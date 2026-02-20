#ifndef DICT_H
#define DICT_H

#include "tfobj.h"


void dict_add(tf_vm *vm, const char *name, tfobj *list);
tfobj* dict_lookup(tf_vm *vm, const char *name);
void dict_free(tf_vm *vm);

#endif // !DICT_H
