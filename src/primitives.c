#include "../include/primitives.h"

#include <stddef.h>
#include <stdio.h>

#include "../include/stack.h"
#include "../include/symbol.h"

int tf_exec_prim(tf_vm *vm, int op) {
  switch (op) {
  case TF_PRINT:
    tfprint(vm->stack);
    break;

  case TF_DUP:
    tfdup(vm->stack);
    break;

  case TF_DROP:
    tfdrop(vm->stack);
    break;

  case TF_SWAP:
    tfswap(vm->stack);
    break;

  case TF_OVER:
    tfover(vm->stack);
    break;

  case TF_JMPZ:
    tfjmpz(vm);
    break;

  case TF_JMP:
    tfjmp(vm);
    break;

  /* ===================== THIS WILL NEVER BE EXECUTED ====================== */
  case TF_THEN:
    break;

  case TF_BEGIN:
    break;

  case TF_WHILE:
    break;

  case TF_REPEAT:
    break;
    /* ========================================================================
     */

  case TF_TO_R:
    tf_to_r(vm);
    break;

  case TF_FROM_R:
    tf_from_r(vm);
    break;

  case TF_R_FETCH:
    tf_r_fetch(vm);
    break;

  case TF_DO:
    tf_do(vm);
    break;

  case TF_LOOP:
    tf_loop(vm);
    break;

  case TF_I:
    tf_i(vm);
    break;

  default:
    tfalu(vm->stack, op);
    break;
  }

  return TF_OK;
}

int tfalu(tfobj *stack, int op) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: '%s' needs at least 2 elements.\n",
            prim_names[op]);
    return TF_ERR;
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
    return TF_ERR;
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
    if (b->val == TF_OK) {
      stack_push(stack, a);
      stack_push(stack, b);
      tfobj_release(a);
      tfobj_release(b);
      fprintf(stderr, "TYPE MISMATCH: '/' works only divisor != TF_OK.\n");
      return TF_ERR;
    }

    obj = create_int_object(a->val / b->val);
    break;

  case TF_MOD:
    if (b->val == TF_OK) {
      stack_push(stack, a);
      stack_push(stack, b);
      tfobj_release(a);
      tfobj_release(b);
      fprintf(stderr, "TYPE MISMATCH: '%%' works only divisor != TF_OK.\n");
      return TF_ERR;
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

  return TF_OK;
}

int tfprint(tfobj *stack) {
  if (stack->list.len < 1) {
    fprintf(stderr, "STACK UNDERFLOW: '.' needs at least 1 elements\n");
    return TF_ERR;
  }

  tfobj *obj = stack_pop(stack);

  tfobj_print(obj);
  tfobj_release(obj);

  return TF_OK;
}

int tfdup(tfobj *stack) {
  if (stack->list.len < 1) {
    fprintf(stderr, "STACK UNDERFLOW: 'DUP' needs at least 1 elements\n");
    return TF_ERR;
  }
  tfobj *obj = stack_peek(stack);

  stack_push(stack, obj);

  return TF_OK;
}

int tfdrop(tfobj *stack) {
  if (stack->list.len < 1) {
    fprintf(stderr, "STACK UNDERFLOW: 'DROP' needs at least 1 element\n");
    return TF_ERR;
  }
  tfobj *obj = stack_pop(stack);

  tfobj_release(obj);

  return TF_OK;
}

int tfswap(tfobj *stack) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: 'SWAP' needs at least 2 elements\n");
    return TF_ERR;
  }

  tfobj *first = stack_pop(stack);
  tfobj *second = stack_pop(stack);

  stack_push(stack, first);
  stack_push(stack, second);

  tfobj_release(first);
  tfobj_release(second);

  return TF_OK;
}

int tfover(tfobj *stack) {
  if (stack->list.len < 2) {
    fprintf(stderr, "STACK UNDERFLOW: 'OVER' needs 2 elements\n");
    return TF_ERR;
  }
  tfobj *obj = stack->list.elem[stack->list.len - 2];

  stack_push(stack, obj);
  return TF_OK;
}

int tfjmpz(tf_vm *vm) {
  tfobj *cond = stack_pop(vm->stack);
  int val = cond->val;
  tfobj_release(cond);

  if (val == 1) {
    vm->ip++; // Skip jmpz arg
    return TF_OK;
  }

  return tfjmp(vm);
}

int tfjmp(tf_vm *vm) {
  vm->ip++;
  int jmp_arg = vm->code[vm->ip]->val;
  vm->ip = jmp_arg;
  vm->ip--; // Decreased because it's gonna increment in the end of exec.

  return TF_OK;
}

int tf_to_r(tf_vm *vm) {
  if (vm->stack->list.len < 1) {
    fprintf(stderr, "STACK UNDERFLOW: '>R' needs 1 element on data stack.\n");
    return TF_ERR;
  }
  tfobj *obj = stack_pop(vm->stack);

  stack_push(vm->r_stack, obj);

  tfobj_release(obj);
  return TF_OK;
}

int tf_from_r(tf_vm *vm) {
  if (vm->r_stack->list.len < 1) {
    fprintf(stderr, "RETURN STACK UNDERFLOW: 'R>' needs 1 element.\n");
    return TF_ERR;
  }
  tfobj *obj = stack_pop(vm->r_stack);

  stack_push(vm->stack, obj);

  tfobj_release(obj);
  return TF_OK;
}

int tf_r_fetch(tf_vm *vm) {
  if (vm->r_stack->list.len < 1) {
    fprintf(stderr, "RETURN STACK UNDERFLOW: 'R@' needs 1 element.\n");
    return TF_ERR;
  }
  tfobj *obj = stack_peek(vm->r_stack);

  stack_push(vm->stack, obj);

  return TF_OK;
}

int tf_do(tf_vm *vm) {
  // Sposta limit e start sul Return Stack
  if (vm->stack->list.len < 2)
    return TF_ERR;

  tfobj *start = stack_pop(vm->stack);
  tfobj *limit = stack_pop(vm->stack);

  // Ordine su R-Stack: Limit (sotto), Start (sopra/top)
  stack_push(vm->r_stack, limit);
  stack_push(vm->r_stack, start);

  tfobj_release(start);
  tfobj_release(limit);
  return TF_OK;
}

int tf_loop(tf_vm *vm) {
  // 1. Recupera Indice e Limite dal R-Stack (senza rimuoverli per ora)
  // R-Stack Top: Index
  // R-Stack Top-1: Limit
  size_t len = vm->r_stack->list.len;
  if (len < 2)
    return TF_ERR;

  tfobj *index_obj = vm->r_stack->list.elem[len - 1];
  tfobj *limit_obj = vm->r_stack->list.elem[len - 2];

  // 2. Incrementa Indice
  index_obj->val += 1;

  // 3. Controlla condizione: Index < Limit ?
  if (index_obj->val < limit_obj->val) {
    // CONTINUA IL LOOP: Salta indietro
    // Leggiamo l'indirizzo target (che è l'argomento dopo OP_LOOP)
    int target = vm->code[vm->ip + 1]->val;
    vm->ip = target;
    vm->ip--; // Compensazione per l'incremento del ciclo exec
  } else {
    // FINE LOOP: Pulisci R-Stack e vai avanti
    // Rimuovi Index e Limit
    tfobj *i = stack_pop(vm->r_stack);
    tfobj_release(i);
    tfobj *l = stack_pop(vm->r_stack);
    tfobj_release(l);

    vm->ip++; // Salta l'argomento (indirizzo) del LOOP
  }
  return TF_OK;
}

int tf_i(tf_vm *vm) {
  return tf_r_fetch(vm); // R@ e I sono la stessa cosa!
}
