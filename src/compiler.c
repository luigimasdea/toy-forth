#include "../include/compiler.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/list.h"
#include "../include/memory.h"
#include "../include/parser.h"
#include "../include/symbol.h"

#define MAX_NESTING 64
size_t ctrl_stack[MAX_NESTING];
int ctrl_s_ptr = 0;

char *read_file(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    perror("Opening ToyForth program");
    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  char *prg_text = (char *)xmalloc(file_size + 1);
  fseek(fp, 0, SEEK_SET);
  fread(prg_text, file_size, 1, fp);
  prg_text[file_size] = '\0';
  fclose(fp);

  return prg_text;
}

// FIXME: Fix Edge cases
void backpatching(tfobj *list, int op_type) {
  switch (op_type) {

  case TF_JMPZ: {
    tfobj *hole = create_int_object(-1);
    list_push_back(list, hole);
    tfobj_release(hole);

    if (ctrl_s_ptr >= MAX_NESTING) {
      fprintf(stderr, "ERROR: Nesting too deep\n");
      exit(TF_ERR);
    }
    ctrl_stack[ctrl_s_ptr++] = list->list.len - 1;
    break;
  }

  case TF_JMP: {
    if (ctrl_s_ptr == 0) {
      fprintf(stderr, "ERROR: An ELSE instuction need at least an IF before\n");
      exit(TF_ERR);
    }
    size_t idx = ctrl_stack[--ctrl_s_ptr];

    tfobj *hole = create_int_object(-1);
    list_push_back(list, hole);
    tfobj_release(hole);

    list->list.elem[idx]->val = list->list.len;

    ctrl_stack[ctrl_s_ptr++] = list->list.len - 1;

    break;
  }

  case TF_THEN: {
    tfobj *temp_obj = list_pop_back(list);
    tfobj_release(temp_obj);

    if (ctrl_s_ptr == 0) {
      fprintf(stderr, "ERROR: A THEN instuction need at least an IF before\n");
      exit(TF_ERR);
    }
    size_t idx = ctrl_stack[--ctrl_s_ptr];

    list->list.elem[idx]->val = list->list.len;

    break;
  }

  case TF_BEGIN: {
    tfobj *temp_obj = list_pop_back(list);
    tfobj_release(temp_obj);

    if (ctrl_s_ptr >= MAX_NESTING) {
      fprintf(stderr, "ERROR: Nesting too deep at BEGIN\n");
      exit(TF_ERR);
    }

    ctrl_stack[ctrl_s_ptr++] = list->list.len;
    break;
  }

  case TF_WHILE: {
    tfobj *temp_obj = list_pop_back(list);
    tfobj_release(temp_obj);

    tfobj *op = create_symbol_object(TF_JMPZ);
    list_push_back(list, op);
    tfobj_release(op);

    tfobj *hole = create_int_object(-1);
    list_push_back(list, hole);
    tfobj_release(hole);

    if (ctrl_s_ptr >= MAX_NESTING) {
      fprintf(stderr, "ERROR: Nesting too deep at WHILE\n");
      exit(TF_ERR);
    }

    ctrl_stack[ctrl_s_ptr++] = list->list.len - 1;
    break;
  }

  case TF_REPEAT: {
    tfobj *temp_obj = list_pop_back(list);
    tfobj_release(temp_obj);

    if (ctrl_s_ptr < 2) {
      fprintf(stderr, "Error: REPEAT without BEGIN/WHILE\n");
      exit(TF_ERR);
    }

    size_t while_hole_idx = ctrl_stack[--ctrl_s_ptr];

    size_t begin_addr = ctrl_stack[--ctrl_s_ptr];

    tfobj *op = create_symbol_object(TF_JMP);
    list_push_back(list, op);
    tfobj_release(op);

    tfobj *target = create_int_object((int)begin_addr);
    list_push_back(list, target);
    tfobj_release(target);

    list->list.elem[while_hole_idx]->val = (int)list->list.len;

    break;
  }

  case TF_DO: {
    // DO compila codice! Deve spostare argomenti su R-Stack.
    // Ma a differenza di BEGIN, qui emettiamo un'istruzione reale.
    // Poiché "DO" è una primitiva runtime, la lasciamo nella lista (o la
    // sostituiamo con un opcode dedicato).

    // Se nel tuo parser DO è mappato a un Opcode TF_DO che esegue la logica
    // runtime, allora qui dobbiamo solo gestire il salto (il target per il
    // LOOP).

    // NOTA: In molti Forth, DO è "immediato" e compila codice complesso.
    // Per semplicità nel ToyForth: Trattiamo DO come marcatore di inizio loop.

    // 1. NON rimuovere TF_DO dalla lista istruzioni, serve a runtime!
    // (Oppure assicurati che list_push_back l'abbia messo prima di chiamare
    // backpatching)

    // 2. Salva l'indirizzo dell'istruzione DOPO il DO (qui inizia il loop)
    ctrl_stack[ctrl_s_ptr++] = list->list.len;
    break;
  }

  case TF_LOOP: {
    // 1. Rimuovi il simbolo "LOOP" (lo sostituiamo con logica di salto)
    tfobj *temp = list_pop_back(list);
    tfobj_release(temp);

    if (ctrl_s_ptr == 0) {
      fprintf(stderr, "ERROR: LOOP without DO\n");
      exit(TF_ERR);
    }

    // 2. Recupera l'indirizzo dopo il DO
    size_t do_addr = ctrl_stack[--ctrl_s_ptr];

    // 3. Emetti istruzione TF_LOOP (Runtime)
    // Questa istruzione farà: (R: limit index -- ) increment index, check limit
    tfobj *op = create_symbol_object(TF_LOOP);
    list_push_back(list, op);
    tfobj_release(op);

    // 4. Emetti l'indirizzo di salto (dove tornare se il loop continua)
    tfobj *target = create_int_object((int)do_addr);
    list_push_back(list, target);
    tfobj_release(target);
    break;
  }
  }
}

tfobj *compile(char *prg) {
  tfparser parser;
  parser.prg = prg;
  parser.p = prg;

  tfobj *obj;
  tfobj *parsed_list = create_list_object();

  while (parser.p) {
    char *token_start = parser.p;
    skip_spaces(&parser);

    if (parser.p[0] == '\0') {
      break; /* EOF */
    }

    /* Parsing different types */
    if (isdigit(parser.p[0]) || (parser.p[0] == '-' && isdigit(parser.p[1]))) {
      obj = parse_int(&parser);
    } else if (strncmp(parser.p, "S\" ", 3) == 0) {
      parser.p += 3;
      obj = parse_string(&parser);
    } else {
      obj = parse_symbol(&parser);
    }

    if (obj == NULL) {
      fprintf(stderr, "UNDEFINED WORD: %s\n", token_start);
      continue;
    }

    list_push_back(parsed_list, obj);

    if (obj->type == TFOBJ_TYPE_SYMBOL) {
      backpatching(parsed_list, obj->val);
    }

    tfobj_release(obj);
  }

  return parsed_list;
}
