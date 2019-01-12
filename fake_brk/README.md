# brk hook

## only for x86_64 linux
[hidden symbolの関数呼び出しをフックする \- Okiraku Programming]( http://neocat.hatenablog.com/entry/20111225/1324823705 )

NOTE: you can't use `printf` inside of `brk`

----

If you want hook `gethostbyname2`, you can add below codes!
```
#include <netdb.h>
struct hostent *gethostbyname2_hook(const char *name, int af) {
  struct hostent *ret = gethostbyname2(name, af);
  printf("# gethostbyname2(%s, %d)\n", name, af);
  return ret;
}
HookInstaller(gethostbyname2, gethostbyname2_hook);
```

`getenv`
```
#include <stdlib.h>
char *getenv_hook(const char *name) {
  char *ret = getenv(name);
  printf("# getenv(%s)\n", name);
  return ret;
}
HookInstaller(getenv, getenv_hook);
```
