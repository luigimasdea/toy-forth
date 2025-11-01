#ifndef STACK_H
#define STACK_H

#include "tfobj.h"

void tf_stack_push(tfobj *stack, tfobj *elem);
tfobj *tf_stack_pop(tfobj *stack);

#endif // !STACK_H
