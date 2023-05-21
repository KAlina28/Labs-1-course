#include "point_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void remove_point(intrusive_list *list, int x, int y) {
    intrusive_node *tmp = list->head;
    while (tmp != NULL) {
        point *p = container_of(tmp, struct point, node);
        if (p->x == x && p->y == y) {
            intrusive_node *to_remove = tmp;
            tmp = tmp->next;
            remove_node(list, to_remove);
            free(container_of(to_remove, struct point, node));
        } else {
            tmp = tmp->next;
        }
    }
}


void add_point(intrusive_list *list , int x, int y)
{
    point *new_node = (point*)malloc(sizeof(struct point));
    assert(new_node);
    new_node->x = x;
    new_node->y = y;
    add_node(list , &new_node->node);
}

void remove_all_points(intrusive_list *list){
    intrusive_node *tmp = list->head;
    while (tmp != NULL){
        intrusive_node *p = tmp;
        tmp = tmp->next;
        remove_node(list, p);
        free(container_of(p, struct point, node));
    }
}


void show_all_points(intrusive_node *node, char *s) {
    point *p = container_of(node, struct point, node);
    printf(s, p->x, p->y);
}
