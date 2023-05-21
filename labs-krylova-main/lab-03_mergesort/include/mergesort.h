#ifndef LAB_03__MERGESORT_MERGESORT_H
#define LAB_03__MERGESORT_MERGESORT_H

typedef unsigned long size_t;

void merge_sort(
        void *array,
        size_t elements, size_t element_size,
        int (*comparator)(const void *, const void *)
);

#endif //LAB_03__MERGESORT_MERGESORT_H
