#include "primitives.h"

#include <stdio.h>

#include "stack.h"
#include "tfobj.h"

/* IMPORTANT: NO CHECKS, NO RELEASES */

int tfadd(tfobj *stack) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: '+' needs at least 2 elements\n");
    return -1;
  }
  
  tfobj *b = stack_pop(stack);
  tfobj *a = stack_pop(stack);

  if (a->type != TFOBJ_TYPE_INT || b->type != TFOBJ_TYPE_INT) {
    stack_push(stack, a);
    stack_push(stack, b);
    fprintf(stderr, "TYPE MISMATCH: '+' works only with integers\n");
    return -1;
  }
  tfobj *obj = create_int_object(a->val + b->val);

  tfobj_release(a);
  tfobj_release(b);

  stack_push(stack, obj);

  return 0;
}

int tfsub(tfobj *stack) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: '-' needs at least 2 elements\n");
    return -1;
  }
  
  tfobj *b = stack_pop(stack);
  tfobj *a = stack_pop(stack);

  if (a->type != TFOBJ_TYPE_INT || b->type != TFOBJ_TYPE_INT) {
    fprintf(stderr, "TYPE MISMATCH: '-' works only with integers\n");
    return -1;
  }
  tfobj *obj = create_int_object(a->val - b->val);
  stack_push(stack, obj);

  return 0;
}

int tfmul(tfobj *stack) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: '*' needs at least 2 elements\n");
    return -1;
  }
  
  tfobj *b = stack_pop(stack);
  tfobj *a = stack_pop(stack);

  if (a->type != TFOBJ_TYPE_INT || b->type != TFOBJ_TYPE_INT) {
    fprintf(stderr, "TYPE MISMATCH: '*' works only with integers\n");
    return -1;
  }
  tfobj *obj = create_int_object(a->val * b->val);
  stack_push(stack, obj);

  return 0;
}

int tfdiv(tfobj *stack) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: '/' needs at least 2 elements\n");
    return -1;
  }
  
  tfobj *b = stack_pop(stack);
  tfobj *a = stack_pop(stack);

  if (a->type != TFOBJ_TYPE_INT || b->type != TFOBJ_TYPE_INT) {
    fprintf(stderr, "TYPE MISMATCH: '/' works only with integers\n");
    return -1;
  }
  tfobj *obj = create_int_object(a->val / b->val);
  stack_push(stack, obj);

  return 0;
}

int tfprint(tfobj *stack) {
  if (stack->list.len < 1) {
    fprintf(stderr, "STACK UNDERFLOW: '.' needs at least 1 elements\n");
    return -1;
  }
  
  tfobj *obj = stack_pop(stack);

  tfobj_print(obj);
  tfobj_release(obj);

  return 0;
}

int tfdup(tfobj *stack) {
  if (stack->list.len < 1) {
    fprintf(stderr, "STACK UNDERFLOW: 'DUP' needs at least 1 elements\n");
    return -1;
  }
  tfobj *obj = stack_peek(stack);

  if (obj->type != TFOBJ_TYPE_INT) {
    fprintf(stderr, "TYPE MISMATCH: 'Dup' only works with integers\n");
    return -1;
  }

  tfobj *dup = create_int_object(obj->val);

  stack_push(stack, dup);

  return 0;
}

int tfmod(tfobj *stack) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: 'MOD' needs at least 2 elements\n");
    return -1;
  }
  
  tfobj *b = stack_pop(stack);
  tfobj *a = stack_pop(stack);

  if (a->type != TFOBJ_TYPE_INT || b->type != TFOBJ_TYPE_INT) {
    fprintf(stderr, "TYPE MISMATCH: 'MOD' works only with integers\n");
    return -1;
  }
  tfobj *obj = create_int_object(a->val % b->val);
  stack_push(stack, obj);

  return 0;
}
