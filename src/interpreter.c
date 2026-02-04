#include "../include/interpreter.h"

#include <stdio.h>
#include <string.h>

#include "../include/compiler.h"
#include "../include/exec.h"

void interpreter(tf_vm *vm) {
  char buf[CHARS_READ_PER_LINE];
  tfobj *tokens_list;

  while(1) {
    printf("> ");
    if (fgets(buf, CHARS_READ_PER_LINE, stdin) == NULL) {
      printf("\nEOF signal (Ctrl+D) detected. Exiting program.\n");
      break;
    }

    if (strncmp(buf, "quit", 4) == 0
      || strncmp(buf, "bye", 3) == 0) {
      break;
    }

    tokens_list = compile(buf, vm);

    if (tokens_list == NULL) continue;

    exec(vm, tokens_list);

    tfobj_release(tokens_list);
  }
}
