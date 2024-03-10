#include "tarb.h"

int main(int argc, char *argv[]) {
    FILE *fp = NULL;  // initializare fisiere
    FILE *out = NULL;
    int factor = 0;
    if (strcmp(argv[1], "-c1") == 0 || strcmp(argv[1], "-c2") == 0) {
        factor = atoi(argv[2]);  // extragere factor din linia de comanda
        fp = fopen(argv[3], "rb");  // deschidere fisiere
        out = fopen(argv[4], "w");
    }
    if (strcmp(argv[1], "-d") == 0) {
        fp = fopen(argv[2], "rb");  // deschidere fisiere
        out = fopen(argv[3], "w");
    }
    char tip[3];
    int width = 0, height = 0, maxval = 0;
    if (fp == NULL) {  // verificare daca fisierele au fost deschise
        printf("EROARE");
        return 1;
    }
    if (out == NULL) {
        printf("EROARE");
        return 1;
    }
    fscanf(fp, "%s\n%d %d\n%d", tip, &width, &height, &maxval);  // citire antet
    char back = 0;
    fscanf(fp, "%c", &back);

    // aloc memorie pentru informatiile despre pixeli
    unsigned char *pixeli = (unsigned char *)malloc(width * height * 3);

    // citesc valorile pixelilor
    fread(pixeli, sizeof(unsigned char), width * height * 3, fp);

    int i = 0;
    unsigned char **red = NULL, **green = NULL, **blue = NULL;
    red = (unsigned char **)malloc(width * sizeof(unsigned char *));  // alocare pentru vector de pointeri
    for (i = 0; i < width; i++)
        red[i] = malloc(height * sizeof(unsigned char));  // alocare pentru o linie si initializare la zero

    green = malloc(width * sizeof(unsigned char *));  // alocare pentru vector de pointeri
    for (i = 0; i < width; i++)
        green[i] = malloc(height * sizeof(unsigned char));  // alocare pentru o linie si initializare la zero

    blue = malloc(width * sizeof(unsigned char *));  // alocare pentru vector de pointeri
    for (i = 0; i < width; i++)
        blue[i] = malloc(height * sizeof(unsigned char));  // alocare pentru o linie si initializare la zero

    // umplu matricele pentru fiecare culoare
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width * 3 + j * 3;
            red[i][j] = pixeli[index];
            green[i][j] = pixeli[index + 1];
            blue[i][j] = pixeli[index + 2];
        }
    }

    TArb arb = divizare(red, green, blue, factor, 0, 0, width);  // creare arbore de compresie
    int rez = nrniv(arb);
    if (strcmp(argv[1], "-c1") == 0) {  // pt cerinta 1
        fprintf(out, "%d\n", rez);  // printez datele corespunzatoare in fisier
        unsigned long long int nrf = nrfrunze(arb);
        fprintf(out, "%lld\n", nrf);
        unsigned long long int dim = width;
        int niv_min = rez;
        detniv(arb, 0, &niv_min);
        for (i = 0; i < niv_min; i++)
            dim /= 2;
        fprintf(out, "%lld\n", dim);
    }
    if (strcmp(argv[1], "-c2") == 0) {  // pentru cerinta 2
        fwrite(&width, sizeof(unsigned int), 1, out);  // printez datele corespunzatoare in fisier
        for (i = 0; i < rez; i++)
            noduriniv(arb, 0, i, out);
    }
    // eliberez memoria
    free(pixeli);
    for (i = 0; i < width; i++)
        free(red[i]);
    free(red);
    for (i = 0; i < width; i++)
        free(green[i]);
    free(green);
    for (i = 0; i < width; i++)
        free(blue[i]);
    free(blue);
    DistrArb(&arb);
    // inchid fiserele
    fclose(fp);
    fclose(out);
    return 0;
}
