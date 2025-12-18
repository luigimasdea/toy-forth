#ifndef COMPILER_H
#define COMPILER_H

#include "tfobj.h"

char *read_file(char *path);
void backpatching(tfobj *list, int op_type);
tfobj *compile(char *prg);

#endif // !COMPILER_H
