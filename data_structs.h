#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include <stdlib.h>

typedef struct tfobj {
  int ref_count;
  int type;  // TFOBJ_TYPE_*
  union {
    int i;
    struct {
      char *str_ptr;
      size_t len;
    } str;

    struct {
      struct tfobj **list_ptr;
      size_t len;
    } list;
  };
} tfobj;

typedef struct tf_parser {
  char *prg;  // The progam to compile into a list
  char *p;  // Next token to parse
} tf_parser;

#endif // !DATA_STRUCTS_H
