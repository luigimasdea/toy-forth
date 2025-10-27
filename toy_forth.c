#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

enum TFOBJ_TYPE {
  TFOBJ_TYPE_INT = 0,
  TFOBJ_TYPE_BOOL = 1,
  TFOBJ_TYPE_STRING = 2,
  TFOBJ_TYPE_LIST = 3,
  TFOBJ_TYPE_SYMBOL = 4,
};

/* ============================ Data Structures ============================ */

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
      struct tfobj **elem;
      size_t len;
    } list;
  };
} tfobj;

void *xmalloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Bad memory allocation");
    exit(EXIT_FAILURE);
  }

  return ptr;
}

/* ======================= Object Related Functions ======================== */

tfobj *create_object(int type) {
  tfobj *obj = xmalloc(sizeof(tfobj));
  obj->ref_count = 1;
  obj->type = type;

  return obj;
}

tfobj *create_int_object(int i) {
  tfobj *obj = create_object(TFOBJ_TYPE_INT);
  obj->i = i;

  return obj;
}

tfobj *create_bool_object(int i) {
  tfobj *obj = create_object(TFOBJ_TYPE_BOOL);
  obj->i = i;

  return obj;
}

tfobj *create_string_object(char *str_ptr, size_t len) {
  tfobj *obj = create_object(TFOBJ_TYPE_STRING);
  obj->str.str_ptr = str_ptr;
  obj->str.len = len;

  return obj;
}

tfobj *create_list_object(void) {
  tfobj *obj = create_object(TFOBJ_TYPE_LIST);
  obj->list.elem = NULL;
  obj->list.len = 0;

  return obj;
}

/* ================================= Main ================================== */

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
  }

  tfobj *tf_stack = create_list_object();
}
