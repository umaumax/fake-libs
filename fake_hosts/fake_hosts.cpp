#include <dlfcn.h>
#include <pwd.h>
#include <unistd.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void parse_hosts(std::function<bool(std::string, std::string)> lambda) {
  // NOTE: priority
  // 1. $FAKE_HOSTS_FILEPATH
  // 2. ./.hosts
  // 3. ~/.hosts
  std::vector<std::string> hosts_filepathes;

  // 1. $FAKE_HOSTS_FILEPATH
  const char *tmp_hosts_filepath;
  if ((tmp_hosts_filepath = std::getenv("FAKE_HOSTS_FILEPATH"))) {
    hosts_filepathes.emplace_back(std::string(tmp_hosts_filepath));
  }
  // 2. ./.hosts
  hosts_filepathes.emplace_back("./.hosts");
  // 3. ~/.hosts
  {
    struct passwd *pw   = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    hosts_filepathes.emplace_back(std::string(homedir) + "/.hosts");
  }

  for (auto &&hosts_filepath : hosts_filepathes) {
    std::string line;
    std::ifstream ifs(hosts_filepath);
    if (ifs.is_open()) {
      while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string from_name, to_name;
        ss >> from_name;
        if (from_name.find("#") != std::string::npos) {
          continue;
        }
        ss >> to_name;

        if (lambda(from_name, to_name)) {
          break;
        }
      }
      break;
    }
  }
}
std::string conv_resolve_host(std::string pathname) {
  std::string new_pathname_str(pathname);
  parse_hosts([&](std::string from_name, std::string to_name) {
    if (pathname == from_name) {
      new_pathname_str = to_name;
      return true;
    }
    return false;
  });
  return new_pathname_str;
}

extern "C" {
int inet_aton(const char *cp, struct in_addr *inp) {
  using libc_inet_aton_pointer_type                 = decltype(&inet_aton);
  static libc_inet_aton_pointer_type libc_inet_aton = nullptr;
  if (libc_inet_aton == nullptr) {
    libc_inet_aton = (libc_inet_aton_pointer_type)dlsym(RTLD_NEXT, "inet_aton");
    assert(libc_inet_aton && "failed dlsym inet_aton");
  }

  return libc_inet_aton(conv_resolve_host(std::string(cp)).c_str(), inp);
}

struct hostent *gethostbyname2(const char *name, int af) {
  using libc_gethostbyname2_pointer_type                      = decltype(&gethostbyname2);
  static libc_gethostbyname2_pointer_type libc_gethostbyname2 = nullptr;
  if (libc_gethostbyname2 == nullptr) {
    libc_gethostbyname2 = (libc_gethostbyname2_pointer_type)dlsym(RTLD_NEXT, "gethostbyname2");
    assert(libc_gethostbyname2 && "failed dlsym gethostbyname2");
  }

  return libc_gethostbyname2(conv_resolve_host(std::string(name)).c_str(), af);
}
}
