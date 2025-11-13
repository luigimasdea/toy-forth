#include "symbol.h"

#include <ctype.h>
#include <string.h>
#include <stddef.h>

#define PRIM_COUNT 7

const tfprim_dictionary_entry primitives[PRIM_COUNT] = {
    {"+", tfadd},
    {"-", tfsub},
    {"*", tfmul},
    {"/", tfdiv},
    {".", tfprint},
    {"DUP", tfdup},
    {"MOD", tfmod},
};

char *strupr(char *str) {
  char *start = str;

  while (*str) {
    *str = toupper((unsigned char) *str);
    ++str;
  }

  return start;
}

tfprim getprim(char *str) {
  for (int i = 0; i < PRIM_COUNT; ++i) {
    if (strcmp(strupr(str), primitives[i].symbol) == 0) {
      return primitives[i].prim_ptr;
    }
  }

  return NULL;
}
