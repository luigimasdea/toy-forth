#include "exec.h"

#include "stack.h"


void exec(tfobj *stack, tfobj *list) {
  for (size_t i = 0; i < list->list.len; ++i) {

    tfobj *el = list->list.elem[i];

    switch (el->type) {
      case TFOBJ_TYPE_INT:
        stack_push(stack, el);
        break;

      case TFOBJ_TYPE_SYMBOL:
        /* Call the function relative to symbol */
        break;

      default:
        break;
    }
  }
}
