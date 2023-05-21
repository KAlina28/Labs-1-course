#ifndef LABS_KRYLOVA_CLIST_H
#define LABS_KRYLOVA_CLIST_H
#include <stddef.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))


typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
}intrusive_node;

typedef struct intrusive_list {
    struct intrusive_node *head;
    struct intrusive_node *tail;
}intrusive_list;


void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data);




void init_list(intrusive_list *list);
void add_node(intrusive_list *list , intrusive_node *new_node);
void remove_node(intrusive_list *list, intrusive_node *node);
void count (intrusive_node *node, void *data);

#endif //LABS_KRYLOVA_CLIST_H
