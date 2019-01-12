#include <dlfcn.h>
#include <openssl/ssl.h>
#include <unistd.h>

#include <cassert>

extern "C" {
int SSL_write(SSL *context, const void *buffer, int bytes) {
  using libc_SSL_write_pointer_type                 = decltype(&SSL_write);
  static libc_SSL_write_pointer_type libc_SSL_write = nullptr;
  if (libc_SSL_write == nullptr) {
    libc_SSL_write = (libc_SSL_write_pointer_type)dlsym(RTLD_NEXT, "SSL_write");
    assert(libc_SSL_write && "failed dlsym SSL_write");
  }
  {
    FILE *logfile = fopen("SSL_write.log", "a+");
    fprintf(logfile, "# Process %d:\n# Header\n%s\n\n", getpid(), (char *)buffer);
    fclose(logfile);
  }
  return libc_SSL_write(context, buffer, bytes);
}
}
