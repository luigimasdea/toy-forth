#ifndef LIST_H
#define LIST_H

#include "tfobj.h"

void list_push_front(tfobj *list, tfobj *elem);
void list_push_back(tfobj *list, tfobj *elem);
tfobj *list_pop_front(tfobj *list);
tfobj *list_pop_back(tfobj *list);
void list_print(tfobj *list);

#endif // !LIST_H
