#include "stack.h"

#include <stdio.h>

#include "tfobj.h"
#include "memory.h"

/*
* This function tries to push an element to the stack. First it checks that the
* 'stack' parameter type is 'LIST', then it reallocates the list and push the element.
* Finally, it increases the element's ref_count
*/
void stack_push(tfobj *stack, tfobj *elem) {
  if (stack->type != TFOBJ_TYPE_STACK) {
    fprintf(stderr, "Pushed to a non-stack tfobject");
    exit(EXIT_FAILURE);
  }

  size_t new_len = stack->list.len + 1;

  stack->list.elem = (tfobj **) xreallocarray(stack->list.elem, new_len, sizeof(tfobj *));

  stack->list.elem[stack->list.len] = elem;
  stack->list.len = new_len;

  tfobj_retain(elem);
}

/*
 * This function check if stack is 'LIST', then checks if stack is not empty,
 * finally pops and returns the element on top 
 * IMPORTANT: If the return object is acquired, you need to retain it.
 */
tfobj *stack_pop(tfobj *stack) {
  if (stack->type != TFOBJ_TYPE_STACK) {
    fprintf(stderr, "Popped from a non-stack tfobject");
    exit(EXIT_FAILURE);
  }

  if (stack->list.len <= 0) {
    fprintf(stderr, "Popped from an empty stack");
    exit(EXIT_FAILURE);
  }

  size_t new_len = stack->list.len - 1;
  
  tfobj *pop_obj = stack->list.elem[new_len];

  /* If 'new_len' == 0, xreallocarray becomes a free call (maybe there are portabilty issues) */
  stack->list.elem = (tfobj **) xreallocarray(stack->list.elem, new_len, sizeof(tfobj *));

  stack->list.len = new_len;

  tfobj_release(pop_obj);

  return pop_obj;
}
