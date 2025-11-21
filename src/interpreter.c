#include "../include/interpreter.h"

#include <stdio.h>
#include <string.h>

#include "../include/compiler.h"
#include "../include/exec.h"

void interpreter(tfobj *stack) {
  char buf[CHARS_READ_PER_LINE];
  tfobj *tokens_list;

  while(1) {
    printf("> ");
    if (fgets(buf, CHARS_READ_PER_LINE, stdin) == NULL) {
      printf("\nEOF signal (Ctrl+D) detected. Exiting program.\n");
      exit(EXIT_SUCCESS); 
    }

    if (strncmp(buf, "quit", 4) == 0
      || strncmp(buf, "bye", 3) == 0) {
      break;
    }

    tokens_list = compile(buf);
    if (tokens_list == NULL) break;
    exec(stack, tokens_list);

    tfobj_release(tokens_list);
  }
}
