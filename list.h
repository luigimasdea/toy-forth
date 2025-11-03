#ifndef LIST_H
#define LIST_H

#include "tfobj.h"

void list_push_front(tfobj *list, tfobj *elem);
void list_push_back(tfobj *list, tfobj *elem);
tfobj *list_get_front(tfobj *list);
tfobj *list_get_back(tfobj *list);
void list_remove_front(tfobj *list);
void list_remove_back(tfobj *list);

#endif // !LIST_H
