#include "interpreter.h"

#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "exec.h"

void interpreter(tfobj *stack) {
  char buf[CHARS_READ_PER_LINE];
  tfobj *tokens_list;

  while(1) {
    printf("> ");
    if (fgets(buf, CHARS_READ_PER_LINE, stdin) == NULL) {
      printf("\nEOF signal (Ctrl+D) detected. Exiting program.\n");
      exit(EXIT_SUCCESS); 
    }

    if (strncmp(buf, "quit", 4) == 0) {
      break;
    }

    tokens_list = compile(buf);
    if (tokens_list == NULL) break;
    exec(stack, tokens_list);

    // list_print(stack);

    tfobj_release(tokens_list);
  }
}
