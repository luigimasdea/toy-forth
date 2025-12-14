#include "../include/exec.h"

#include "../include/stack.h"
#include "../include/list.h"
#include "../include/primitives.h"


void exec(tfobj *stack, tfobj *list) {
  while (list->list.len > 0) {

    tfobj *el = list_pop_back(list);

    switch (el->type) {
      case TFOBJ_TYPE_SYMBOL:
        tfprim(stack, el->val);
        break;

      default:
        stack_push(stack, el);
        break;
    }

    tfobj_release(el);
  }
}
