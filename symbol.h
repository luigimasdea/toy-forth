#ifndef SYMBOL_H
#define SYMBOL_H

#include "tfobj.h"
#include "primitives.h"

typedef struct {
    char *symbol; 
    tfprim prim_ptr;
} tfprim_dictionary_entry;

char *strupr(char *str);
tfprim getprim(char *str);

#endif // !SYMBOL_H
