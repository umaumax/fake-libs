#include <dlfcn.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define LIB_PATH "libc.so.6"

template <class RET, class... ARGV>
class LibHook {
 public:
  typedef RET rtype;
  typedef RET (*ftype)(ARGV...);

 protected:
  void *handle, *func;
  ftype hook;
  unsigned char origcode[14], jumpcode[14];

 public:
  LibHook(const char *libpath, const char *funcname, ftype hook) : hook(hook) {
    handle = dlopen(libpath, RTLD_NOW);
    if (!handle) err(1, "dlopen failed");
    func = dlsym(handle, funcname);
    if (!func) err(1, "dlshm failed");

    unsigned long addr = (unsigned long)hook;
    memcpy(origcode, func, sizeof(origcode));
    memcpy(jumpcode, (const unsigned char[]){0xff, 0x25, 0, 0, 0, 0}, 6);  //jmp *(%rip)
    memcpy(jumpcode + 6, &addr, sizeof(addr));

    addr = (unsigned long)func;
    mprotect((void *)(addr & ~0xfff), (addr & 0xfff) < 4096 - 14 ? 4096 : 8192, PROT_WRITE | PROT_READ | PROT_EXEC);
  }
  ~LibHook() {
    unsigned long addr = (unsigned long)func;
    mprotect((void *)(addr & ~0xfff), (addr & 0xfff) < 4096 - 14 ? 4096 : 8192, PROT_READ | PROT_EXEC);
    dlclose(handle);
  }

  void setAutoRemove(ftype hook) {
    unsigned long addr = (unsigned long)hook;
    memcpy(jumpcode + 6, &addr, sizeof(addr));
  }

  void install() { memcpy(func, jumpcode, sizeof(jumpcode)); }
  void uninstall() { memcpy(func, origcode, sizeof(origcode)); }

  // remove jump to call original func within the hook
  RET _autoRemoveHook(ARGV... args) {
    uninstall();
    RET ret = hook(args...);
    install();
    return ret;
  }
  template <LibHook *obj>
  static RET autoRemoveHook(ARGV... args) {
    return obj->_autoRemoveHook(args...);
  }
};

template <class RET, class... ARGS>
LibHook<RET, ARGS...> _resolve_ftype(RET (*f)(ARGS...)) {
  throw "This function must not be called.";
  return LibHook<RET, ARGS...>();
}

#define HookInstaller(func, hfunc)                        \
  namespace NSHook_##func {                               \
    typedef decltype(_resolve_ftype(func)) HookT;         \
    HookT hook(LIB_PATH, #func, hfunc);                   \
    struct Installer {                                    \
      Installer() {                                       \
        hook.setAutoRemove(HookT::autoRemoveHook<&hook>); \
        hook.install();                                   \
      }                                                   \
    } installer;                                          \
  };
