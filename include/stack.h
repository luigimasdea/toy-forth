#ifndef STACK_H
#define STACK_H

#include "tfobj.h"

void stack_push(tfobj *stack, tfobj *elem);
tfobj *stack_pop(tfobj *stack);
tfobj *stack_peek(tfobj *stack);

#endif // !STACK_H
