#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define puts_stderr(message)              \
  {                                       \
    /* NOTE: stderr:2 */                  \
    write(2, (message), strlen(message)); \
  }

#ifdef __APPLE__
extern "C" {
void *malloc(size_t size);
// void *realloc(void *ptr, size_t size);
// void *calloc(size_t nmemb, size_t size);
// int posix_memalign(void **memptr, size_t alignment, size_t size) throw();
void free(void *p);
}
#else
void *malloc(size_t size);
void *realloc(void *ptr, size_t size) throw();
void *calloc(size_t nmemb, size_t size);
int posix_memalign(void **memptr, size_t alignment, size_t size) throw();
void free(void *p);
#endif

#ifdef __APPLE__
extern "C" {
#endif

void *malloc(size_t sz) {
  static void *(*libc_malloc)(size_t) = nullptr;
  static unsigned long long int cnt   = 0;
  if (nullptr == libc_malloc) libc_malloc = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
  cnt++;
  if (cnt % 1000000 == 1) puts_stderr("# logmalloc: malloc called!\n");
  return libc_malloc(sz);
}

void free(void *p) {
  static void (*libc_free)(void *);
  static unsigned long long int cnt = 0;
  if (nullptr == libc_free) libc_free = (void (*)(void *))dlsym(RTLD_NEXT, "free");
  cnt++;
  if (cnt % 1000000 == 1) puts_stderr("# logmalloc: free called!\n");
  libc_free(p);
  return;
}

#ifdef __APPLE__
}
#endif
