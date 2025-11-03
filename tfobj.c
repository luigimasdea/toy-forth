#include "tfobj.h"

#include "memory.h"
#include <stdlib.h>

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

tfobj *create_symbol_object(char *str_ptr, size_t len) {
  tfobj *obj = create_string_object(str_ptr, len);
  obj->type = TFOBJ_TYPE_SYMBOL;

  return obj;
}

tfobj *create_list_object(void) {
  tfobj *obj = create_object(TFOBJ_TYPE_LIST);
  obj->list.elem = NULL;
  obj->list.len = 0;

  return obj;
}

tfobj *create_stack_object(void) {
  tfobj *obj = create_list_object();
  obj->type = TFOBJ_TYPE_STACK;

  return obj;
}

void tfobj_retain(tfobj *obj) {
  obj->ref_count++;
}

void tfobj_release(tfobj *obj) {
  obj->ref_count--;

  if (obj->ref_count <= 0) {
    free(obj);
  }
}
