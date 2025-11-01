#include "tfobj.h"

#include "memory.h"

tfobj *create_object(int type) {
  tfobj *obj = (tfobj*) xmalloc(sizeof(tfobj));
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
  obj->list.list_ptr = NULL;
  obj->list.len = 0;

  return obj;
}
