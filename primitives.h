#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "tfobj.h"

int tfadd(tfobj *stack);
int tfsub(tfobj *stack);
int tfmul(tfobj *stack);
int tfdiv(tfobj *stack);
int tfprint(tfobj *stack);
int tfdup(tfobj *stack);
int tfmod(tfobj *stack);

#endif // !PRIMITIVES_H
