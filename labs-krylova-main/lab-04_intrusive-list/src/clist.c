#include "clist.h"
#include <stddef.h>

void init_list(intrusive_list *list) {
    list->head = NULL;
    list->size = 0;
}

void add_node(intrusive_list *list , intrusive_node *new_node)
{
    list->size += 1;
    if (list->head == NULL){
        list->head = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }else {
        new_node->next = list->head;
        list->head->prev = new_node;
        new_node->prev = NULL;
        list->head = new_node;
    }
}
void remove_node(intrusive_list *list, intrusive_node *node){
    list->size -= 1;
    if (node->next != NULL){
        node->next->prev = node->prev;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
}

int get_length(intrusive_list *list) {
    return list->size;
}






