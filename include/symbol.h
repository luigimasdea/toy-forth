#ifndef SYMBOL_H
#define SYMBOL_H

#include "tfobj.h"

enum Opcode {
  TF_ADD = 0,
  TF_SUB,
  TF_MUL,
  TF_DIV,
  TF_PRINT,
  TF_DUP,
  TF_MOD,
  TF_LT,
  TF_GT,
  TF_EQ,
  TF_LE,
  TF_GE,
  TF_NE,
  TF_JMPZ,
  TF_JMP,
  TF_THEN,
  TF_DROP,
  TF_BEGIN,
  TF_WHILE,
  TF_REPEAT,
  PRIM_COUNT,
};

extern const char *prim_names[];

char *strupr(char *str);
int get_prim_num(char *str);

#endif // !SYMBOL_H
