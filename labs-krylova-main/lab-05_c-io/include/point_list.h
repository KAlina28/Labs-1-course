#ifndef LABS_KRYLOVA_POINT_LIST_H
#define LABS_KRYLOVA_POINT_LIST_H
#include "clist.h"

typedef struct point {
    int x, y;
    struct intrusive_node node;
}point;

void show_all_points(intrusive_node *node, char *s);
void add_point(intrusive_list *list, int x, int y);
void remove_point(intrusive_list *list, int x, int y);
void remove_all_points(intrusive_list *list);

#endif //LABS_KRYLOVA_POINT_LIST_H
