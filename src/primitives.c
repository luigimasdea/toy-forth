#include "../include/primitives.h"

#include <stdio.h>

#include "../include/stack.h"
#include "../include/symbol.h"

int tfprim(tfobj *stack, int op) {
  switch (op) {
  case TF_PRINT:
    tfprint(stack);
    break;

  case TF_DUP:
    tfdup(stack);
    break;

  default:
    tfalu(stack, op);
    break;
  }

  return 0;
}

int tfalu(tfobj *stack, int op) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: '%s' needs at least 2 elements.\n",
            prim_names[op]);
    return -1;
  }

  tfobj *b = stack_pop(stack);
  tfobj *a = stack_pop(stack);

  if (!TF_IS_NUMERIC(a->type) || !TF_IS_NUMERIC(b->type)) {
    stack_push(stack, a);
    stack_push(stack, b);
    tfobj_release(a);
    tfobj_release(b);
    fprintf(stderr, "TYPE MISMATCH: '%s' works only with integers.\n",
            prim_names[op]);
    return -1;
  }

  tfobj *obj;
  switch (op) {
  case TF_ADD:
    obj = create_int_object(a->val + b->val);
    break;

  case TF_SUB:
    obj = create_int_object(a->val - b->val);
    break;

  case TF_MUL:
    obj = create_int_object(a->val * b->val);
    break;

  case TF_DIV:
    if (b->val == 0) {
      stack_push(stack, a);
      stack_push(stack, b);
      tfobj_release(a);
      tfobj_release(b);
      fprintf(stderr, "TYPE MISMATCH: '/' works only divisor != 0.\n");
      return -1;
    }

    obj = create_int_object(a->val / b->val);
    break;

  case TF_MOD:
    if (b->val == 0) {
      stack_push(stack, a);
      stack_push(stack, b);
      tfobj_release(a);
      tfobj_release(b);
      fprintf(stderr, "TYPE MISMATCH: '%%' works only divisor != 0.\n");
      return -1;
    }

    obj = create_int_object(a->val % b->val);
    break;

  case TF_LT:
    obj = create_bool_object(a->val < b->val);
    break;

  case TF_GT:
    obj = create_bool_object(a->val > b->val);
    break;

  case TF_EQ:
    obj = create_bool_object(a->val == b->val);
    break;

  case TF_LE:
    obj = create_bool_object(a->val <= b->val);
    break;

  case TF_GE:
    obj = create_bool_object(a->val >= b->val);
    break;

  case TF_NE:
    obj = create_bool_object(a->val != b->val);
    break;
  }

  stack_push(stack, obj);

  tfobj_release(a);
  tfobj_release(b);
  tfobj_release(obj);

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

/* FIXME: Add support for other types */
int tfdup(tfobj *stack) {
  if (stack->list.len < 1) {
    fprintf(stderr, "STACK UNDERFLOW: 'DUP' needs at least 1 elements\n");
    return -1;
  }
  tfobj *obj = stack_peek(stack);

  if (obj->type != TFOBJ_TYPE_INT) {
    fprintf(stderr, "TYPE MISMATCH: 'DUP' only works with integers\n");
    return -1;
  }

  stack_push(stack, obj);

  return 0;
}
