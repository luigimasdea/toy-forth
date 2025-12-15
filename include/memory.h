#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

#include "../include/tfobj.h"

void *xmalloc(size_t size);
void *xrealloc(void *p, size_t size);
void *xreallocarray(void *p, size_t n, size_t size);

#endif // !MEMORY_H
