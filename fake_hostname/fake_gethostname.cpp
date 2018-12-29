#include <dlfcn.h>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

extern "C" {
int gethostname(char *name, std::size_t len) {
  using libc_gethostname_pointer_type                   = decltype(&gethostname);
  static libc_gethostname_pointer_type libc_gethostname = nullptr;
  if (libc_gethostname == nullptr) {
    libc_gethostname = (libc_gethostname_pointer_type)dlsym(RTLD_NEXT, "gethostname");
    assert(libc_gethostname && "failed dlsym gethostname");
  }

  char *hostname = std::getenv("FAKE_HOSTNAME");
  if (hostname == nullptr) {
    return libc_gethostname(name, len);
  }

  std::strncpy(name, hostname, len - 1);
  name[len - 1] = '\0';
  return 0;
}
}
