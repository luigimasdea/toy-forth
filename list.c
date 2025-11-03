#include "list.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "tfobj.h"

void list_push_front(tfobj *list, tfobj *elem) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  size_t new_len = list->list.len + 1;
  list->list.elem = (tfobj **) xreallocarray(list->list.elem, new_len, sizeof(tfobj *));

  memmove(list->list.elem + 1, list->list.elem, list->list.len * sizeof(tfobj *));
  list->list.elem[0] = elem;
  list->list.len = new_len;

  tfobj_retain(elem);
}

void list_push_back(tfobj *list, tfobj *elem) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  size_t new_len = list->list.len + 1;
  list->list.elem = (tfobj **) xreallocarray(list->list.elem, new_len, sizeof(tfobj *));

  list->list.elem[list->list.len] = elem;
  list->list.len = new_len;

  tfobj_retain(elem);
}

tfobj *list_get_front(tfobj *list) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  tfobj *e = list->list.elem[0];
  tfobj_retain(e);

  return e;
}

tfobj *list_get_back(tfobj *list) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  tfobj *e = list->list.elem[list->list.len - 1];
  tfobj_retain(e);

  return e;
}

void list_remove_front(tfobj *list) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  size_t new_len = list->list.len - 1;
  tfobj_release(list->list.elem[0]);
  memmove(list->list.elem, list->list.elem + 1, new_len * sizeof(tfobj *));
  list->list.elem = (tfobj **) xreallocarray(list->list.elem, new_len, sizeof(tfobj *));
  list->list.len = new_len;
}

void list_remove_back(tfobj *list) {
  if (list == NULL || list->type != TFOBJ_TYPE_LIST) {
    fprintf(stderr, "Argoument is a non-list tfobject");
    exit(EXIT_FAILURE);
  }

  size_t new_len = list->list.len - 1;
  tfobj_release(list->list.elem[list->list.len - 1]);
  list->list.elem = (tfobj **) xreallocarray(list->list.elem, new_len, sizeof(tfobj *));
  list->list.len = new_len;
}
