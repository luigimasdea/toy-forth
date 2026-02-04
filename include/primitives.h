#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "tfobj.h"
#include <stddef.h>

int tf_exec_prim(tf_vm *vm, int op);
int tfalu(tfobj *stack, int op);
int tfprint(tfobj *stack);
int tfdup(tfobj *stack);
int tfdrop(tfobj *stack);
int tfswap(tfobj *stack);
int tfover(tfobj *stack);
int tfjmpz(tf_vm *vm);
int tfjmp(tf_vm *vm);
int tf_to_r(tf_vm *vm);
int tf_from_r(tf_vm *vm);
int tf_r_fetch(tf_vm *vm);
int tf_do(tf_vm *vm);
int tf_loop(tf_vm *vm);
int tf_i(tf_vm *vm);

#endif // !PRIMITIVES_H
