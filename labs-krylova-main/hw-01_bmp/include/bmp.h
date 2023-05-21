#ifndef LABS_KRYLOVA_BMP_H
#define LABS_KRYLOVA_BMP_H

#include <stdio.h>

#pragma pack(push, 2)

typedef struct BMPHeader {
    unsigned short type;
    unsigned int size;
    unsigned int reserved;
    unsigned int pixel_offset;
} BMPHeader;

typedef struct DIBHeader {
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short color_planes;
    unsigned short bit_per_pixel;
    unsigned int compression;
    unsigned int pixels_bsize;
    unsigned int x_pels_pel_meter;
    unsigned int y_pels_pel_meter;
    unsigned int color_used;
    unsigned int imp_color;
} DIBHeader;

typedef struct BMPFile {
    BMPHeader *bmpHeader;
    DIBHeader *dibHeader;
    void *data;
} BMPFile;
#pragma pack(pop)

int load_bmp (FILE *f, BMPFile *file);
int crop (BMPFile *file, int x, int y, int w, int h);
int rotate (BMPFile *file);
int save_bmp (FILE *outfile, BMPFile *file);

#endif //LABS_KRYLOVA_BMP_H
