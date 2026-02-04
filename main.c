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

  tfobj *data_stack = create_stack_object();
  tfobj *ret_stack = create_stack_object();

  tf_vm vm;
  vm.stack = data_stack;
  vm.r_stack = ret_stack;
  vm.dict = NULL;
  vm.ip = 0;
  vm.code = NULL;
  vm.len = 0;

  if (argc == 2) {
    char *prg_text = read_file(argv[1]);
    tfobj *ls = compile(prg_text, &vm);
    exec(&vm, ls);

    free(prg_text);
    tfobj_release(ls);
  }

  interpreter(&vm);

  tfobj_release(data_stack);
  tfobj_release(ret_stack);

  // TODO: Free dictionary

  return 0;
}
