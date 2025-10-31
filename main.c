#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

#include "data_structs.h"

#define CHARS_READ_PER_LINE 33  // 32 bytes + 1 to store '\0'

enum TFOBJ_TYPE {
  TFOBJ_TYPE_INT = 0,
  TFOBJ_TYPE_BOOL = 1,
  TFOBJ_TYPE_STRING = 2,
  TFOBJ_TYPE_LIST = 3,
  TFOBJ_TYPE_SYMBOL = 4,
};

// enum TDOBJ_SYMBOLS {
//   TFOBJ_SYM_ADD = "+",
//   TFOBJ_SYM_SUBTRACT = "-",
//   TFOBJ_SYM_MULTIPLY = "*",
//   TFOBJ_SYM_DIVIDE = "/"
// };

/* ============================ Data Structures ============================= */


/* ============================= Wrappers =================================== */

void *wmalloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Bad memory allocation");
    exit(EXIT_FAILURE);
  }

  return ptr;
}

void *wrealloc(void *p, size_t size) {
  void *ptr = realloc(p, size);
  if (ptr == NULL) {
    fprintf(stderr, "Bad memory reallocation");
    exit(EXIT_FAILURE);
  }

  return ptr;
}

void *wreallocarray(void *p, size_t n, size_t size) {
  void *ptr = reallocarray(p, n, size);
  if (ptr == NULL) {
    fprintf(stderr, "Bad memory reallocation");
    exit(EXIT_FAILURE);
  }

  return ptr;
}

/* ======================= Object Related Functions ========================= */

tfobj *create_object(int type) {
  tfobj *obj = (tfobj*) wmalloc(sizeof(tfobj));
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

/* ======================= Stack Related Functions ========================== */

/* This function tries to push an element to the stack. First it checks that the 'stack' parameter type is 'LIST', then it reallocates the list and push the element. Finally, it increases the element's ref_count */
void tf_stack_push(tfobj *stack, tfobj *elem) {
  if (stack->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Pushed to a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  size_t new_len = stack->list.len + 1;

  stack->list.list_ptr = (tfobj**) wreallocarray(stack->list.list_ptr, new_len, sizeof(tfobj));

  stack->list.list_ptr[stack->list.len] = elem;
  stack->list.len = new_len;

  elem->ref_count++;
}

/* This function check if stack is 'LIST', then checks if stack is not empty, finally pops and returns the element on top */
tfobj *tf_stack_pop(tfobj *stack) {
  if (stack->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Popped from a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  if (stack->list.len <= 0) {
    fprintf(stderr, "Popped from an empty stack");
    exit(EXIT_FAILURE);
  }

  size_t new_len = stack->list.len - 1;
  
  tfobj *pop_obj = stack->list.list_ptr[new_len];

  if (new_len > 0) {
    stack->list.list_ptr = (tfobj**) wreallocarray(stack->list.list_ptr, new_len, sizeof(tfobj));
  } else {
    free(stack->list.list_ptr); 
    stack->list.list_ptr = NULL;
  }

  stack->list.len = new_len;

  pop_obj->ref_count--;

  return pop_obj;
}

/* ================================= Main =================================== */

int main(void) {
  /* Manage keywords
  I need a map, symbol as keys, functions pointers as values. When a symbol 
  (e.g. '+') is popped from the stack, i need to call `map['+'];`.
  A symbol is essentially a string. How do I understand when it's one or another?
  First of all, I need an enum */

  /* First, I'm gonna develop an interpreter */
  tfobj *tf_stack = create_list_object();

  char buf[CHARS_READ_PER_LINE];

  while(1) {
    printf(" > Inserisci: ");
    fgets(buf, sizeof(buf), stdin);
    // printf("%s\n", buf);
  }
  return 0;
}
