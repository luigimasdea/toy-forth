#ifndef SYMBOL_H
#define SYMBOL_H

#include "tfobj.h"

#define X_PRIMITIVES \
    X(TF_ADD,     "+") \
    X(TF_SUB,     "-") \
    X(TF_MUL,     "*") \
    X(TF_DIV,     "/") \
    X(TF_PRINT,   ".") \
    X(TF_DUP,     "DUP") \
    X(TF_MOD,     "MOD") \
    X(TF_LT,      "<") \
    X(TF_GT,      ">") \
    X(TF_EQ,      "==") \
    X(TF_LE,      "<=") \
    X(TF_GE,      ">=") \
    X(TF_NE,      "!=") \
    X(TF_JMPZ,    "IF") \
    X(TF_JMP,     "ELSE") \
    X(TF_THEN,    "THEN") \
    X(TF_DROP,    "DROP") \
    X(TF_SWAP,    "SWAP") \
    X(TF_BEGIN,   "BEGIN") \
    X(TF_WHILE,   "WHILE") \
    X(TF_REPEAT,  "REPEAT") \
    X(TF_TO_R,    ">R") \
    X(TF_FROM_R,  "R>") \
    X(TF_R_FETCH, "R@")

#define X(opcode, name) opcode,

enum Opcode {
  X_PRIMITIVES
  PRIM_COUNT 
};

#undef X

extern const char *prim_names[];

char *strupr(char *str);
int get_prim_num(char *str);

#endif // !SYMBOL_H
