#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "bmp.h"
void freeBMP(BMPFile *bmpFile){
    free(bmpFile->dibHeader);
    free(bmpFile->bmpHeader);
    free(bmpFile->data);
}

int main(int argc, char* argv[]) {
    if (argc != 8) {
        fprintf(stderr, "Некорректный ввод.\n");
        return 1;
    }


    FILE *f = fopen(argv[2], "rb");
    if (!f) {
        fprintf(stderr, "Нет файла.\n");
        return 1;
    }
    int result;
    BMPFile bmpFile;
    result = load_bmp(f, &bmpFile);

    if (result) {
        fprintf(stderr, "Входной файл некорректен.\n");
        freeBMP(&bmpFile);
        fclose(f);
        return 1;
    }

    if (bmpFile.dibHeader->bit_per_pixel != 24) {
        fprintf(stderr, "Неправильный формат файла.\n");
        freeBMP(&bmpFile);
        fclose(f);
        return 1;
    }

    if (strcmp(argv[1], "crop-rotate") == 0) {
        int x = atoi(argv[4]);
        int y = atoi(argv[5]);
        int w = atoi(argv[6]);
        int h = atoi(argv[7]);

        int w_file = bmpFile.dibHeader->width;
        int h_file = bmpFile.dibHeader->height;

        if ((x < 0) || (y < 0) || (w <=  0) || (h <= 0) || (y > h_file - h)|| (x > w_file - w)) {
            fprintf(stderr, "Аргументы некорректны.\n");
            return 1;
        }
        crop(&bmpFile, x, y, w, h);
        rotate(&bmpFile);

        FILE *outfile = fopen(argv[3], "wb");
        if (!outfile) {
            fprintf(stderr, "Нет файла.\n");
            freeBMP(&bmpFile);
            fclose(f);
            return 1;
        }

        result = save_bmp(outfile, &bmpFile);
        freeBMP(&bmpFile);
        fclose(f);
        fclose(outfile);

        if (result) {
            fprintf(stderr, "Запись не корректна.\n");
            return 1;
        }
        return 0;
    }
    return 1;
}
