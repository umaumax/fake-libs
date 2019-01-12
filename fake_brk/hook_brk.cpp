#include <stdio.h>
#include <unistd.h>
#include "LibHook.h"

#define puts_stderr(message)              \
  {                                       \
    /* NOTE: stderr:2 */                  \
    write(2, (message), strlen(message)); \
  }

int brk_hook(void *addr) {
  int ret = brk(addr);
  // 	printf("brk(%p) => %d\n", addr, ret);
  puts_stderr("# brk_hook called!\n");
  return ret;
}
HookInstaller(brk, brk_hook);
