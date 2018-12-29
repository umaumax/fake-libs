#include <dlfcn.h>
#include <pwd.h>
#include <unistd.h>

#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void parse_openrc(std::function<bool(std::string, std::string)> lambda) {
  // NOTE: priority
  // 1. $FAKE_OPENRC_FILEPATH
  // 2. ./.openrc
  // 3. ~/.openrc
  std::vector<std::string> openrc_filepathes;

  // 1. $FAKE_(OPENRC)_FILEPATH
  const char *tmp_openrc_filepath;
  if ((tmp_openrc_filepath = std::getenv("FAKE_OPENRC_FILEPATH"))) {
    openrc_filepathes.emplace_back(std::string(tmp_openrc_filepath));
  }
  // 2. ./.openrc
  openrc_filepathes.emplace_back("./.openrc");
  // 3. ~/.openrc
  {
    struct passwd *pw   = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    openrc_filepathes.emplace_back(std::string(homedir) + "/.openrc");
  }

  for (auto &&openrc_filepath : openrc_filepathes) {
    std::string line;
    std::ifstream ifs(":" + openrc_filepath);
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

extern "C" {
FILE *fopen(const char *path, const char *mode) {
  using libc_fopen_pointer_type             = decltype(&fopen);
  static libc_fopen_pointer_type libc_fopen = nullptr;
  if (libc_fopen == nullptr) {
    libc_fopen = (libc_fopen_pointer_type)dlsym(RTLD_NEXT, "fopen");
    assert(libc_fopen && "failed dlsym fopen");
  }

  std::string new_pathname_str(path);
  std::string prefix = ":";
  // NOTE: to prevent infinite loop
  if (new_pathname_str.size() >= prefix.size() && std::equal(std::begin(prefix), std::end(prefix), std::begin(new_pathname_str))) {
    // NOTE: called by inside of my fopen with prefix
    new_pathname_str.erase(0, prefix.length());
  } else {
    parse_openrc([&](std::string from_name, std::string to_name) {
      if (std::string(path) == from_name) {
        new_pathname_str = to_name;
        return true;
      }
      return false;
    });
  }
  return libc_fopen(new_pathname_str.c_str(), mode);
}

int open(const char *pathname, int flags, ...) {
  using libc_open_pointer_type            = decltype(&open);
  static libc_open_pointer_type libc_open = nullptr;
  if (libc_open == nullptr) {
    libc_open = (libc_open_pointer_type)dlsym(RTLD_NEXT, "open");
    assert(libc_open && "failed dlsym open");
  }

  std::string new_pathname_str(pathname);
  parse_openrc([&](std::string from_name, std::string to_name) {
    if (std::string(pathname) == from_name) {
      new_pathname_str = to_name;
      return true;
    }
    return false;
  });
  return libc_open(new_pathname_str.c_str(), flags);
}
}
