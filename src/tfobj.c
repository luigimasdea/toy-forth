#include "../include/tfobj.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/memory.h"

tfobj *create_object(int type) {
  tfobj *obj = (tfobj*) xmalloc(sizeof(tfobj));
  obj->ref_count = 1;
  obj->type = type;

  return obj;
}

tfobj *create_int_object(int val) {
  tfobj *obj = create_object(TFOBJ_TYPE_INT);
  obj->val = val;

  return obj;
}

tfobj *create_bool_object(int val) {
  tfobj *obj = create_object(TFOBJ_TYPE_BOOL);

  if (val != 0 && val != 1) {
    fprintf(stderr, "Error: bool object value must be 0 or 1\n");
  }
  obj->val = val;

  return obj;
}

tfobj *create_string_object(char *str_ptr, size_t len) {
  tfobj *obj = create_object(TFOBJ_TYPE_STRING);
  obj->str.str_ptr = str_ptr;
  obj->str.len = len;

  return obj;
}

tfobj *create_symbol_object(tfprim prim) {
  tfobj *obj = create_object(TFOBJ_TYPE_SYMBOL);
  obj->prim_ptr = prim;

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

void tfobj_free(tfobj *obj) {
  switch (obj->type) {
    case TFOBJ_TYPE_LIST:
    case TFOBJ_TYPE_STACK:
      for (size_t i = 0; i < obj->list.len; ++i) {
        tfobj_free(obj->list.elem[i]);
      }
      break;

    case TFOBJ_TYPE_STRING:
      free(obj->str.str_ptr);
      break;

    default:
      break;

    free(obj);
  }
}

void tfobj_retain(tfobj *obj) {
  if (obj == NULL) {
    return;
  }

  obj->ref_count++;
}

void tfobj_release(tfobj *obj) {
  assert(obj != NULL && obj->ref_count > 0);

  obj->ref_count--;

  if (obj->ref_count == 0) {
    tfobj_free(obj);
  }
}

void tfobj_print(tfobj *obj) {
  if (obj == NULL) {
    printf("[NULL]");
    return;
  }

  switch (obj->type) {
    case TFOBJ_TYPE_INT:
      printf("%d\n", obj->val);
      break;

    case TFOBJ_TYPE_BOOL:
      if (obj->val == 0) {
        printf("TRUE");
      } else {
        printf("FALSE");
      }
      break;

    default:
      fprintf(stderr, "Print of other types is not yet implemented\n");
      exit(EXIT_FAILURE);
      break;
  }
}
