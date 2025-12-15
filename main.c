#include <stdio.h>
#include <stdlib.h>

#include "include/exec.h"
#include "include/tfobj.h"
#include "include/interpreter.h"
#include "include/compiler.h"

int main(int argc, char **argv) {
  if (argc > 2) {
    fprintf(stderr, "Usage: main <file>");
    exit(TF_ERR);
  }

  tfobj *tfstack = create_stack_object();

  if (argc == 2) {
    char *prg_text = read_file(argv[1]);
    tfobj *ls = compile(prg_text);
    exec(tfstack, ls);

    free(prg_text);
    tfobj_release(ls);
  }

  interpreter(tfstack);

  tfobj_release(tfstack);

  return 0;
}
