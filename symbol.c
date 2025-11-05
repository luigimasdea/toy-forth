#include "symbol.h"

#include <string.h>
#include <stddef.h>

const char *symbols[] = { "+", "-", "*", "/", ".", "DUP" };

/* Maybe I need to put this in symbol object constructor */
int issymbol(char *str) {
  for (int i = 0; i < 6; ++i) {
    if (strcmp(str, symbols[i]) == 0) {
      return 1;
    }
  }

  return 0;
}
