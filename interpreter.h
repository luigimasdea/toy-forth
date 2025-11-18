#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "tfobj.h"

#define CHARS_READ_PER_LINE 129  // 129 bytes + 1 to store '\0'

void interpreter(tfobj *stack);

#endif // !INTERPRETER_H
