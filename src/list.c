#include "../include/list.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../include/memory.h"
#include "../include/tfobj.h"

void list_push_front(tfobj *list, tfobj *elem) {
  if (list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject\n");
    exit(EXIT_FAILURE);
  }
  if (list == NULL || elem == NULL) {
    fprintf(stderr, "One of all of the argouments are NULL\n");
    exit(EXIT_FAILURE);
  }

  size_t new_len = list->list.len + 1;
  list->list.elem = (tfobj **) xreallocarray(list->list.elem, new_len, sizeof(tfobj *));

  memmove(list->list.elem + 1, list->list.elem, list->list.len * sizeof(tfobj *));
  list->list.elem[0] = elem;
  list->list.len = new_len;
}

void list_push_back(tfobj *list, tfobj *elem) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject\n");
    exit(EXIT_FAILURE);
  }

  size_t new_len = list->list.len + 1;
  list->list.elem = (tfobj **) xreallocarray(list->list.elem, new_len, sizeof(tfobj *));

  list->list.elem[list->list.len] = elem;
  list->list.len = new_len;
}

tfobj *list_pop_front(tfobj *list) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject\n");
    exit(EXIT_FAILURE);
  }

  tfobj *e = list->list.elem[0];
  size_t new_len = list->list.len - 1;
  memmove(list->list.elem, list->list.elem + 1, new_len * sizeof(tfobj *));
  list->list.elem = (tfobj **) xreallocarray(list->list.elem, new_len, sizeof(tfobj *));
  list->list.len = new_len;

  return e;
}

tfobj *list_pop_back(tfobj *list) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject\n");
    exit(EXIT_FAILURE);
  }

  tfobj *e = list->list.elem[list->list.len - 1];
  size_t new_len = list->list.len - 1;
  list->list.elem = (tfobj **) xreallocarray(list->list.elem, new_len, sizeof(tfobj *));
  list->list.len = new_len;

  return e;
}

void list_print(tfobj *list) {
  for (size_t i = 0; i < list->list.len; ++i) {
    tfobj_print(list->list.elem[i]);
    printf(" ");
  }
  printf("\n");
}
