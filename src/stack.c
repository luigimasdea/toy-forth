#include "../include/stack.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/tfobj.h"
#include "../include/memory.h"

/*
* This function tries to push an element to the stack.
*/
void stack_push(tfobj *stack, tfobj *elem) {
  if (stack == NULL || elem == NULL) {
    fprintf(stderr, "One of all of the argouments are NULL\n");
    exit(TF_ERR);
  }
  if (stack->type != TFOBJ_TYPE_STACK) {
    fprintf(stderr, "Pushed to a non-stack tfobject\n");
    exit(TF_ERR);
  }

  size_t new_len = stack->list.len + 1;

  stack->list.elem = (tfobj **) xreallocarray(stack->list.elem, new_len, sizeof(tfobj *));

  stack->list.elem[stack->list.len] = elem;
  stack->list.len = new_len;
  tfobj_retain(elem);
}

/*
 * The function pops and returns the element on top of the stack.
 * IMPORTANT: It's up to the caller to release the object when it's acquired.
 */
tfobj *stack_pop(tfobj *stack) {
  if (stack == NULL) {
    fprintf(stderr, "Argoument 'stack' is NULL\n");
    exit(TF_ERR);
  }
  if (stack->type != TFOBJ_TYPE_STACK) {
    fprintf(stderr, "Popped from a non-stack tfobject\n");
    exit(TF_ERR);
  }

  if (stack->list.len <= 0) {
    fprintf(stderr, "Popped from an empty stack\n");
    exit(TF_ERR);
  }

  size_t new_len = stack->list.len - 1;
  
  tfobj *elem = stack->list.elem[new_len];

  /* If 'new_len' == 0, xreallocarray becomes a free call */
  stack->list.elem = (tfobj **) xreallocarray(stack->list.elem, new_len, sizeof(tfobj *));

  stack->list.len = new_len;

  return elem;
}

tfobj *stack_peek(tfobj *stack) {
  if (stack == NULL) {
    fprintf(stderr, "Argoument 'stack' is NULL\n");
    exit(TF_ERR);
  }
  if (stack->type != TFOBJ_TYPE_STACK) {
    fprintf(stderr, "Peeked from a non-stack tfobject\n");
    exit(TF_ERR);
  }

  if (stack->list.len <= 0) {
    fprintf(stderr, "Peeked from an empty stack\n");
    exit(TF_ERR);
  }

  return stack->list.elem[stack->list.len - 1];
}
