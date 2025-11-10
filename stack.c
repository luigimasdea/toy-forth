#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#include "tfobj.h"
#include "memory.h"

/*
* This function tries to push an element to the stack.
*/
void stack_push(tfobj *stack, tfobj *elem) {
  if (stack == NULL || elem == NULL) {
    fprintf(stderr, "One of all of the argouments are NULL\n");
    exit(EXIT_FAILURE);
  }
  if (stack->type != TFOBJ_TYPE_STACK) {
    fprintf(stderr, "Pushed to a non-stack tfobject\n");
    exit(EXIT_FAILURE);
  }

  size_t new_len = stack->list.len + 1;

  stack->list.elem = (tfobj **) xreallocarray(stack->list.elem, new_len, sizeof(tfobj *));

  stack->list.elem[stack->list.len] = elem;
  stack->list.len = new_len;
}

/*
 * The function pops and returns the element on top of the stack.
 * It release the element popped because we retained it when we pushed 
 * it onto the stack.
 * IMPORTANT: It's up to the caller to retain the object if it's acquired.
 */
tfobj *stack_pop(tfobj *stack) {
  if (stack == NULL) {
    fprintf(stderr, "Argoument 'stack' is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (stack->type != TFOBJ_TYPE_STACK) {
    fprintf(stderr, "Popped from a non-stack tfobject\n");
    exit(EXIT_FAILURE);
  }

  if (stack->list.len <= 0) {
    fprintf(stderr, "Popped from an empty stack\n");
    exit(EXIT_FAILURE);
  }

  size_t new_len = stack->list.len - 1;
  
  tfobj *elem = stack->list.elem[new_len];

  /* If 'new_len' == 0, xreallocarray becomes a free call (maybe there are portabilty issues) */
  stack->list.elem = (tfobj **) xreallocarray(stack->list.elem, new_len, sizeof(tfobj *));

  stack->list.len = new_len;

  return elem;
}

tfobj *stack_peek(tfobj *stack) {
  if (stack == NULL) {
    fprintf(stderr, "Argoument 'stack' is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (stack->type != TFOBJ_TYPE_STACK) {
    fprintf(stderr, "Peeked from a non-stack tfobject\n");
    exit(EXIT_FAILURE);
  }

  if (stack->list.len <= 0) {
    fprintf(stderr, "Peeked from an empty stack\n");
    exit(EXIT_FAILURE);
  }

  return stack->list.elem[stack->list.len - 1];
}
