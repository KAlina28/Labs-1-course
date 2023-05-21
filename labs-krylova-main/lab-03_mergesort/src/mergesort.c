#include "mergesort.h"
#include <stdlib.h>
#include <string.h>

void my_memcpy( void* in, void* from, size_t size)
{
    for (int i = 0 ; i < size ; i++)
        ((char *)in)[i] = ((char *)from)[i];
}

void merge_sort(void *array, size_t elements, size_t element_size, int comparator(const void *, const void *)) {
    size_t m = elements / 2;
    if (elements <= 1) {
        return;
    }
    merge_sort(array, m, element_size, comparator);
    merge_sort((char*)array + m * element_size, elements - m, element_size, comparator);
    char *l_ = array;
    char *l = array;
    char *r = (char*)array + m * element_size;
    char *k = malloc(element_size * (elements));
    char *a = k;
    while (l < (char*)array + element_size*m || r < (char*)array + element_size*elements)
    {
        if (l < (char*)array + element_size*m &&
            (r >= (char*)array + element_size*elements || comparator(l, r) <= 0))
        {
            my_memcpy(a,l,element_size);
            l+=element_size;
        }
        else if (r < (char*)array + element_size*elements &&
                 (l >= (char*)array + element_size*m || comparator(l, r) > 0))
        {
            my_memcpy(a, r, element_size);
            r+=element_size;
        }
        a+=element_size;
    }
    my_memcpy(l_, k, element_size * elements);
    free(k);
}






