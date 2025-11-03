#include "memory.h"

#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t size) {
  void *p = malloc(size);
  if (p == NULL) {
    fprintf(stderr, "Bad memory allocation");
    exit(EXIT_FAILURE);
  }

  return p;
}

void *xrealloc(void *p, size_t size) {
  if (size == 0) {
    free(p);
    return NULL;
  }

  void *new_p = realloc(p, size);
  if (new_p == NULL) {
    fprintf(stderr, "Bad memory reallocation");
    exit(EXIT_FAILURE);
  }

  return new_p;
}

void *xreallocarray(void *p, size_t n, size_t size) {
  if (size == 0 || n == 0) {
    free(p);
    return NULL;
  }

  void *new_p= reallocarray(p, n, size);
  if (new_p== NULL) {
    fprintf(stderr, "Bad memory reallocation");
    exit(EXIT_FAILURE);
  }

  return new_p;
}
