#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "tfobj.h"

int tfprim(tfobj *stack, int op);
int tfalu(tfobj *stack, int op);
int tfadd(tfobj *stack);
int tfsub(tfobj *stack);
int tfmul(tfobj *stack);
int tfdiv(tfobj *stack);
int tfprint(tfobj *stack);
int tfdup(tfobj *stack);
int tfmod(tfobj *stack);
int tflt(tfobj *stack);
int tfgt(tfobj *stack);
int tfeq(tfobj *stack);
int tfle(tfobj *stack);
int tfge(tfobj *stack);
int tfne(tfobj *stack);

#endif // !PRIMITIVES_H
