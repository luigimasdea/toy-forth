#include <stdio.h>
#include <string.h>

#include "list.h"
#include "stack.h"
#include "tfobj.h"
#include "parser.h"
#include "exec.h"

#define CHARS_READ_PER_LINE 129  // 129 bytes + 1 to store '\0'

int main(void) {
  /* Manage keywords
  I need a map, symbol as keys, functions pointers as values. When a symbol 
  (e.g. '+') is popped from the stack, i need to call `map['+'];`.
  A symbol is essentially a string. How do I understand when it's one or another?
  First of all, I need an enum */

  /* First, I'm gonna develop an interpreter */
  tfobj *tfstack = create_stack_object();

  char buf[CHARS_READ_PER_LINE];
  tfobj *tokens_list;

  while(1) {
    printf("> ");
    fgets(buf, sizeof(buf), stdin);

    if (strncmp(buf, "quit", 4) == 0) {
      break;
    }

    tokens_list = compile(buf);
    if (tokens_list == NULL) break;
    exec(tfstack, tokens_list);
    list_print(tfstack);
  }
  return 0;
}
