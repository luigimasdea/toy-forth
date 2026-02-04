#include "../include/dict.h"

#include "../include/memory.h"
#include <string.h>

void dict_add(tf_vm *vm, const char *name, tfobj *list) {
    tf_dict_node *node = xmalloc(sizeof(tf_dict_node));
    node->name = strdup(name);
    node->code_list = list;
    tfobj_retain(list); // Incrementa il ref_count perché il dizionario lo possiede
    node->next = vm->dict;
    vm->dict = node;
}

tfobj* dict_lookup(tf_vm *vm, const char *name) {
    tf_dict_node *curr = vm->dict;
    while (curr) {
        if (strcmp(curr->name, name) == 0) return curr->code_list;
        curr = curr->next;
    }
    return NULL;
}
