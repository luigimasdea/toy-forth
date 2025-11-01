#include "stack.h"

#include <stdio.h>

#include "tfobj.h"
#include "memory.h"

/*
* This function tries to push an element to the stack. First it checks that the
* 'stack' parameter type is 'LIST', then it reallocates the list and push the element.
* Finally, it increases the element's ref_count
*/
void tf_stack_push(tfobj *stack, tfobj *elem) {
  if (stack->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Pushed to a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  size_t new_len = stack->list.len + 1;

  stack->list.list_ptr = (tfobj**) xreallocarray(stack->list.list_ptr, new_len, sizeof(tfobj));

  stack->list.list_ptr[stack->list.len] = elem;
  stack->list.len = new_len;

  elem->ref_count++;
}

/*
 * This function check if stack is 'LIST', then checks if stack is not empty,
 * finally pops and returns the element on top 
 */
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
    stack->list.list_ptr = (tfobj**) xreallocarray(stack->list.list_ptr, new_len, sizeof(tfobj));
  } else {
    free(stack->list.list_ptr); 
    stack->list.list_ptr = NULL;
  }

  stack->list.len = new_len;

  pop_obj->ref_count--;

  return pop_obj;
}
