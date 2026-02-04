#include "../include/symbol.h"

#include <ctype.h>
#include <string.h>

#define X(opcode, name) name,

const char *prim_names[] = {
  X_PRIMITIVES
};

#undef X

char *strupr(char *str) {
  char *start = str;

  while (*str) {
    *str = toupper((unsigned char)*str);
    ++str;
  }

  return start;
}

int get_prim_num(char *str) {
  str = strupr(str);
  for (int i = 0; i < PRIM_COUNT; ++i) {
    if (strcmp(str, prim_names[i]) == 0) {
      return i;
    }
  }

  return -1;
}
