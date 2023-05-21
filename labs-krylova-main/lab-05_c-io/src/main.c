#include "clist.h"
#include "point_list.h"
#include <stdio.h>
#include <string.h>

#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))

void read_txt(FILE *f, intrusive_list *list) {
    int x, y;
    while (fscanf(f, "%d %d", &x, &y) == 2) {
        add_point(list, x, y);
    }
}


void read_bin(FILE *f, intrusive_list *l) {
    int x[2] = {0, 0};
    int i = 0;
    while (fread(&(x[i]), 3, 1, f)) {
        if (x[i] > 0x7FFFFF) {
            x[i] = x[i] - 0x1000000;
        }
        i = 1 - i;
        if (i == 0) {
            add_point(l, x[0], x[1]);
            x[0] = 0;
            x[1] = 0;
        }
    }
}


void write_txt(FILE *f, intrusive_list *l) {
    intrusive_node *cur = l->head;
    while (cur) {
        point *p = container_of(cur, point, node);
        fprintf(f, "%d %d\n", p->x, p->y);
        cur = cur->next;
    }
}


void write_bin(FILE *f, intrusive_list *l) {
    intrusive_node *cur = l->head;
    while (cur) {
        point *p = container_of(cur, point, node);
        fwrite(&(p->x), 3, 1, f);
        fwrite(&(p->y), 3, 1, f);
        cur = cur->next;
    }
}


int main(int argc, char *argv[]) {
    intrusive_list l;
    init_list(&l);
    if (argc <= 2)
        return 0;

    if (strcmp(argv[1], "loadtext") == 0) {
        FILE *f = fopen(argv[2], "r");
        read_txt(f, &l);
        fclose(f);
    }

    if (strcmp(argv[1], "loadbin") == 0) {
        FILE *f = fopen(argv[2], "r");
        read_bin(f, &l);
        fclose(f);
    }

    if (argc == 4 && strcmp(argv[3], "count") == 0) {
        int cnt = 0;
        apply(&l, count, &cnt);
        printf("%d\n", cnt);
    }
    if (argc == 5 && strcmp(argv[3], "savetext") == 0) {
        FILE *f = fopen(argv[4], "w");
        write_txt(f, &l);
        fclose(f);
    }
    if (argc == 5 && strcmp(argv[3], "savebin") == 0) {
        FILE *f = fopen(argv[4], "w");
        write_bin(f, &l);
        fclose(f);
    }

    if (argc == 5 && strcmp(argv[3], "print") == 0) {
        apply(&l, show_all_points, argv[4]);
        printf("\n");
    }
    remove_all_points(&l);
    return 0;
}