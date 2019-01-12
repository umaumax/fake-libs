#include <stdio.h>
#include <stdlib.h>

int main(void) {
  free(malloc(256 << 10));
  free(malloc(256 << 10));
  return 0;
}
