#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "bmp.h"

#define format(widht) 3 * widht + widht % 4

static void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;

}
int load_bmp (FILE *f, struct BMPFile *file) {
    void *file_header = malloc(sizeof(BMPHeader));
    if (fread(file_header, sizeof(BMPHeader), 1, f) == 0) {
        return 1;
    }
    file->bmpHeader = file_header;
    if (file->bmpHeader->type != 19778) {
        return 2;
    }

    void *info_header = malloc(sizeof(DIBHeader));
    file->dibHeader = info_header;
    if (fread(info_header, sizeof(DIBHeader), 1, f) == 0) {
        return 1;
    }
    void *pixels = malloc((format(file->dibHeader->width)) * file->dibHeader->height);

    file->data = pixels;
    if ((int)fread(pixels, format(file->dibHeader->width),
                   file->dibHeader->height, f) < file->dibHeader->height) {
        return 1;
    }
    return 0;
}


int crop (BMPFile *file, int x, int y, int w, int h) {
    int old = format(file->dibHeader->width);
    char *old_p = file->data;
    void *new_pixels = calloc(h, format(w));
    char *new_p = new_pixels;

    old_p += (file->dibHeader->height - y - h) * old + 3 * x;
    for(int i = 0; i < h; i++) {
        memcpy(new_p, old_p, 3 * w);
        old_p += old;
        new_p += format(w);
    }

    free(file->data);
    file->data = new_pixels;
    file->dibHeader->pixels_bsize = format(w) * h;
    file->dibHeader->x_pels_pel_meter *= (w / file->dibHeader->width);
    file->dibHeader->y_pels_pel_meter *= (h / file->dibHeader->height);
    file->dibHeader->width = w;
    file->dibHeader->height = h;

    file->bmpHeader->size = file->dibHeader->pixels_bsize + sizeof(BMPHeader) + sizeof(DIBHeader);
    return 0;
}

int rotate (BMPFile *file) {
    int old = format(file->dibHeader->width);
    int new = format(file->dibHeader->height);
    void *new_pixels = calloc(file->dibHeader->width, new);

    char *new_p = new_pixels;
    char *old_p = 0;
    int add = file->dibHeader->height % 4;
    for (int x = 0; x < file->dibHeader->width; x++) {
        old_p = file->data + 3 * (file->dibHeader->width - x - 1);
        for (int y = 0; y < file->dibHeader->height; y++) {
            memcpy(new_p, old_p, 3);
            new_p += 3;
            old_p += old;
        }
        new_p += add;
    }

    free(file->data);
    file->data = new_pixels;

    file->dibHeader->pixels_bsize = new * file->dibHeader->width;
    file->bmpHeader->size = file->dibHeader->pixels_bsize + sizeof(BMPHeader) + sizeof(DIBHeader);
    swap(&file->dibHeader->width, &file->dibHeader->height);
    swap(&file->dibHeader->x_pels_pel_meter, &file->dibHeader->y_pels_pel_meter);

    return 0;
}

int save_bmp (FILE *outfile, BMPFile *file) {
    if (fwrite(file->bmpHeader, sizeof(BMPHeader), 1, outfile) == 0) {
        return 1;
    }
    if (fwrite(file->dibHeader, sizeof(DIBHeader), 1, outfile) == 0) {
        return 1;
    }
    if (fwrite(file->data, file->dibHeader->pixels_bsize, 1, outfile) == 0) {
        return 1;
    }
    return 0;
}
