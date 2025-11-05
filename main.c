#include <stdio.h>
#include <string.h>

#include "list.h"
#include "tfobj.h"
#include "parser.h"
#include "exec.h"

#define CHARS_READ_PER_LINE 129  // 129 bytes + 1 to store '\0'

int main(void) {
  tfobj *tfstack = create_stack_object();

  char buf[CHARS_READ_PER_LINE];
  tfobj *tokens_list;

  while(1) {
    printf("> ");
    if (fgets(buf, CHARS_READ_PER_LINE, stdin) == NULL) {
      printf("\nSegnale EOF (Ctrl+D) rilevato. Chiusura interprete.\n");
      exit(EXIT_SUCCESS); 
    }

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
