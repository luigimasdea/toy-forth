#include <stdio.h>
#include <stdlib.h>

#include "tfobj.h"
#include "interpreter.h"

int main(int argc, char **argv) {
  tfobj *tfstack = create_stack_object();

  if (argc > 2) {
    fprintf(stderr, "Usage: <main> file");
    exit(EXIT_FAILURE);
  }
  else if (argc == 2) {
    /* TODO: compile file */
  }
  else {
    interpreter(tfstack);
  }


  tfobj_release(tfstack);

  return 0;
}
