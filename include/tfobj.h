#ifndef TFOBJ_H
#define TFOBJ_H

#include <stdlib.h>

#define TF_OK 0
#define TF_ERR 1

#define TF_IS_NUMERIC(t) ((t) == TFOBJ_TYPE_INT || (t) == TFOBJ_TYPE_BOOL)

enum TFOBJ_TYPE {
  TFOBJ_TYPE_INT = 0,
  TFOBJ_TYPE_BOOL = 1,
  TFOBJ_TYPE_STRING = 2,
  TFOBJ_TYPE_SYMBOL = 3,
  TFOBJ_TYPE_LIST = 4,
  TFOBJ_TYPE_STACK = 5,
};

struct tfobj;
typedef struct tfobj tfobj;

struct tfobj {
  int ref_count;
  int type;  // TFOBJ_TYPE_*
  union {
    int val;

    struct {
      size_t len;
      char *str_ptr;
    } str;

    struct {
      size_t len;
      struct tfobj **elem;
    } list;
  };
};

typedef struct {
    tfobj *stack;
    tfobj **code;
    size_t ip;
    size_t len;
} tf_vm;

tfobj *create_object(int type);

tfobj *create_int_object(int val);
tfobj *create_bool_object(int val);
tfobj *create_string_object(char *str_ptr, size_t len);
tfobj *create_symbol_object(int prim);
tfobj *create_list_object(void);
tfobj *create_stack_object(void);

void tfobj_free(tfobj *obj);
void tfobj_retain(tfobj *obj);
void tfobj_release(tfobj *obj);

void tfobj_print(tfobj *obj);

#endif // !TFOBJ_H
