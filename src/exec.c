#include "../include/exec.h"

#include "../include/primitives.h"
#include "../include/stack.h"
#include "../include/dict.h"

#include <stdio.h>
#include <stddef.h>

static void exec_internal(tf_vm *vm) {
  while (vm->ip < vm->len) {
    tfobj *el = vm->code[vm->ip];

    switch (el->type) {
    case TFOBJ_TYPE_SYMBOL:
      // Esegue primitive standard (+, -, DUP...)
      tf_exec_prim(vm, el->val);
      break;

    case TFOBJ_TYPE_USER: {
      // 1. Cerca la parola nel dizionario
      // Nota: el->str.str_ptr contiene il nome della parola (es. "SQUARE")
      tfobj *body = dict_lookup(vm, el->str.str_ptr);
      
      if (body == NULL) {
          fprintf(stderr, "ERROR: Unknown word '%s'\n", el->str.str_ptr);
          return; // O exit(TF_ERR)
      }

      // 2. PREPARAZIONE RICORSIONE (Salvataggio Contesto)
      // Creiamo una COPIA della VM sullo stack C.
      // Perché? Perché vm->stack, vm->r_stack e vm->dict sono PUNTATORI,
      // quindi la copia punterà agli stessi oggetti (condivisi).
      // MA vm->ip, vm->code e vm->len saranno locali a questa chiamata.
      tf_vm sub_vm = *vm; 

      // 3. Impostiamo il nuovo codice da eseguire
      sub_vm.ip = 0;
      sub_vm.code = body->list.elem;
      sub_vm.len = body->list.len;

      // 4. Chiamata Ricorsiva!
      // Eseguiamo il corpo della parola definita dall'utente.
      exec_internal(&sub_vm);
      
      // Quando exec_internal ritorna, 'sub_vm' viene distrutta.
      // Noi torniamo al 'vm' originale che ha ancora il suo 'ip' corretto.
      break;
    }

    default:
      // Numeri, Stringhe -> Push sullo stack
      stack_push(vm->stack, el);
      break;
    }

    vm->ip++;
  }
}

void exec(tf_vm *vm, tfobj *list) {
  if (vm == NULL || list == NULL || list->type != TFOBJ_TYPE_LIST) return;

  // Salviamo lo stato precedente della VM (nel caso exec venga chiamata dall'interprete
  // mentre la VM stava facendo altro, anche se raro in questo design)
  tfobj **prev_code = vm->code;
  size_t prev_len = vm->len;
  size_t prev_ip = vm->ip;

  // Impostiamo il nuovo codice
  vm->code = list->list.elem;
  vm->len = list->list.len;
  vm->ip = 0;

  // Avviamo il motore
  exec_internal(vm);

  // Ripristino (opzionale, ma buona pratica per pulizia)
  vm->code = prev_code;
  vm->len = prev_len;
  vm->ip = prev_ip;
}
