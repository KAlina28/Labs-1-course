#include "clist.h"


void init_list(intrusive_list *list) {
    list->head = NULL;
    list->tail = NULL;
}

void add_node(intrusive_list *list , intrusive_node *new_node)
{
    if (list->tail == NULL){
        list->tail = new_node;
        list->head = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        new_node->next = NULL;
        list->tail = new_node;
    }
}



void remove_node(intrusive_list *list, intrusive_node *node){
    if (node->next != NULL){
        node->next->prev = node->prev;
    }else{
        list->head = node->next;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->tail = node->prev;
    }
}


void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data){
    intrusive_node *node = list->head;
    while (node != list->tail->next) {
        op(node, data);
        node = node->next;
    }
}

void count(intrusive_node *node, void *data) {
    (*(int *)data) ++;
}



