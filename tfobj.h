#ifndef TFOBJ_H
#define TFOBJ_H

#include <stdlib.h>

enum TFOBJ_TYPE {
  TFOBJ_TYPE_INT = 0,
  TFOBJ_TYPE_BOOL = 1,
  TFOBJ_TYPE_STRING = 2,
  TFOBJ_TYPE_LIST = 3,
  TFOBJ_TYPE_SYMBOL = 4,
};

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

tfobj *create_object(int type);
tfobj *create_int_object(int i);
tfobj *create_bool_object(int i);
tfobj *create_bool_object(int i);
tfobj *create_list_object(void);

#endif // !TFOBJ_H
