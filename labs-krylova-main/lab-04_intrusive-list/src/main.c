#include "clist.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct point {
    int x, y;
    struct intrusive_node node;
}point;


void add_point(intrusive_list *list , int x, int y)
{
    point *new_node = (point*)malloc(sizeof(struct point));
    new_node->x = x;
    new_node->y = y;
    add_node(list , &new_node->node);
}

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

void show_all_points(intrusive_list *list){
    intrusive_node *tmp = list->head;
    while (tmp != NULL){
        point *p = container_of(tmp, struct point, node);
        printf("(%d %d)", p->x, p->y);
        tmp =  tmp->next;
        if (tmp != NULL)
            printf(" ");

    }
    printf("\n");
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

int main() {
    intrusive_list l;
    init_list(&l);
    char *s = malloc(6 * sizeof(char));
    while (scanf("%6s", s)) {
        if (strcmp(s, "print") == 0) {
            show_all_points(&l);
        } else if (strcmp(s, "rma") == 0) {
            remove_all_points(&l);
        } else if (strcmp(s, "len") == 0) {
            printf("%d", get_length(&l));
            printf("\n");
        } else if (strcmp(s, "add") == 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            add_point(&l, a, b);
        } else if (strcmp(s, "rm") == 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            remove_point(&l, a, b);
        } else if (strcmp(s, "exit") == 0) {
            break;
        } else {
            printf("Unknown command");
            printf("\n");
        }
    }
    remove_all_points(&l);
    free(s);
    return 0;
}

