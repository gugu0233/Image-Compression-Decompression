/*--- tarb.h ---*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifndef ARBORE_BINAR
#define ARBORE_BINAR

typedef struct nod {
    unsigned int info;
    unsigned char tip, r, g, b;
    struct nod *fiu1, *fiu2, *fiu3, *fiu4;
} TNod, *TArb;

/*-- Operatii elementare --*/
TArb ConstrNod(int x, TArb f1, TArb f2, TArb f3, TArb f4);  // returneaza adresa nodului sau NULL daca nu exista spatiu
void distruge(TArb r);
void DistrArb(TArb *a);
int medie(int width, unsigned char **mat, int x, int y);
unsigned long long int calcMEAN(unsigned char **red, unsigned char **green, unsigned char **blue,
int width, int x, int y);
int max_of_four(int a, int b, int c, int d);
int nrniv(TArb r);
int min_of_four(int a, int b, int c, int d);
int detniv(TArb r, int niv, int *niv_minim);
TArb divizare(unsigned char **red, unsigned char **green, unsigned char **blue, int factor, int x, int y, int size);
void noduriniv(TArb arb, int niv, int niv_cautat, FILE *out);
int nrfrunze(TArb r);

#endif

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned int)time(NULL)))
#endif
