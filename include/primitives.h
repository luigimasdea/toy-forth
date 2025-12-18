#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "tfobj.h"
#include <stddef.h>

int tf_exec_prim(tf_vm *vm, int op);
int tfalu(tfobj *stack, int op);
int tfprint(tfobj *stack);
int tfdup(tfobj *stack);
int tfjmpz(tf_vm *vm);
int tfjmp(tf_vm *vm);

#endif // !PRIMITIVES_H
