#include "../include/exec.h"

#include "../include/primitives.h"
#include "../include/stack.h"
#include "../include/symbol.h"
#include <stddef.h>

/*
 * This function take the stack context and the instruction list as argouments.
 * It utilizes an instruction pointer to access the instruction to execute.
 * This pointer need to be incremented by 1 in normal situations, but it has to
 * behave differently when it meets an IF statement. It must check the condition
 * and jump to the body of the if or, eventually, jump to the ELSE body.
 *
 * 1 < 2 IF S" True!" . THEN
 * 2 < 1 IF S" True!" . ELSE S" False" . THEN
 *
 * When we meet an IF, we call TF_JMPZ (conditional jump), becouse we need to
 * evaluate the condition and jump if false. Jump to the ELSE if present,
 * otherwise we jump to the THEN.
 *
 * Instead if we meet an ELSE, it means that the IF was true, so we need to
 * jump unconditionally (TF_JMP).
 */
void exec(tfobj *stack, tfobj *instr_list) {
  if (stack->type != TFOBJ_TYPE_STACK || instr_list->type != TFOBJ_TYPE_LIST)
    return;

  tf_vm vm;
  vm.ip = 0;
  vm.len = instr_list->list.len;
  vm.code = instr_list->list.elem;
  vm.stack = stack;

  while (vm.ip < vm.len) {
    tfobj *el = vm.code[vm.ip];

    switch (el->type) {
    case TFOBJ_TYPE_SYMBOL:
      tf_exec_prim(&vm, el->val);
      break;
    default:
      stack_push(vm.stack, el);
      break;
    }

    vm.ip++;
  }
}
