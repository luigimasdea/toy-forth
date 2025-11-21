#ifndef COMPILER_H
#define COMPILER_H

#include "tfobj.h"
#include "parser.h"

char *read_file(char *path);
tfobj *compile(char *prg);

#endif // !COMPILER_H
