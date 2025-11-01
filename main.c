#include <stdio.h>

#include "tfobj.h"

#define CHARS_READ_PER_LINE 33  // 32 bytes + 1 to store '\0'

int main(void) {
  /* Manage keywords
  I need a map, symbol as keys, functions pointers as values. When a symbol 
  (e.g. '+') is popped from the stack, i need to call `map['+'];`.
  A symbol is essentially a string. How do I understand when it's one or another?
  First of all, I need an enum */

  /* First, I'm gonna develop an interpreter */
  tfobj *tfstack = create_list_object();

  char buf[CHARS_READ_PER_LINE];

  while(1) {
    printf("> Inserisci: ");
    fgets(buf, sizeof(buf), stdin);
    // printf("%s\n", buf);
  }
  return 0;
}
