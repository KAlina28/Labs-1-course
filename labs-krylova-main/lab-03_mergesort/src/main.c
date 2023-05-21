#include "mergesort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int str_comporator(const void *a, const void *b){
    char* s1 = *(char**)a;
    char* s2 = *(char**)b;
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 < *s2) return -1;
        if (*s1 > *s2) return 1;
        s1 ++;
        s2 ++;
    }
    return *s1 == *s2 ? 0 : *s1 == '\0' ? -1 : 1;

}

int char_comporator(const void *a, const void *b){
    return *(const char *)a - *(const char *)b;
}

int int_comporator(const void* a, const void* b)
{
    return *(const int*)a - *(const int*)b;
}

int main(int argc, char** argv) {
    int elements = argc-2;
    void * array;
    if (elements == 0)
        printf("\n");
    else if (strcmp(argv[1], "char")==0) {
        char char_a[elements];
        for (int i = 0; i < elements; ++i){
            char_a[i] = *argv[i+2];
        }
        merge_sort((void*)char_a, elements, sizeof (char), char_comporator);
        for(int i = 0; i < elements;++i){
            printf("%c", char_a[i]);
            if (i < elements - 1)
                printf("%s", " ");
        }
        printf("\n");
    }
    else if (strcmp(argv[1], "int") == 0) {
        long int_a[elements];
        for (int i = 0; i < elements; ++i)
            int_a[i] = strtol(argv[i+2],(char**)NULL, 10);
        merge_sort((void*)int_a, elements, sizeof (long ), int_comporator);
        for(int i = 0; i < elements;++i){
            printf("%ld", int_a[i]);
            if (i < elements - 1)
                printf("%s", " ");
        }
        printf("\n");
    }else {
        char *str_a[elements];
        for (int i = 0; i < elements; ++i){
            str_a[i] = argv[i + 2];
        }
        array = (void*)str_a;
        merge_sort(array, elements, sizeof(str_a[0]), str_comporator);
        for(int i = 0; i < elements;++i){
            printf("%s", str_a[i]);
            if (i < elements - 1)
                printf("%s", " ");
        }
        printf("\n");
    }
}
