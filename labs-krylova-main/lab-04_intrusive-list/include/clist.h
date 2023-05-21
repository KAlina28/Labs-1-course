#ifndef CLIST_H_
#define CLIST_H_
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))
#include <stddef.h>


typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
}intrusive_node;

typedef struct intrusive_list {
    struct intrusive_node *head;
    size_t size;
}intrusive_list;

void init_list(intrusive_list *list);
void add_node(intrusive_list *list , intrusive_node *new_node);
void remove_node(intrusive_list *list, intrusive_node *node);
int get_length(intrusive_list *list);

#endif