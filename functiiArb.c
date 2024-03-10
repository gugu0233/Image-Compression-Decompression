#include "tarb.h"

TArb ConstrNod(int x, TArb f1, TArb f2, TArb f3, TArb f4) {
    TArb aux = (TArb)malloc(sizeof(TNod)); /* alocare spatiu */
    if (!aux)
        return NULL; /* spatiu insuficient */
    aux->info = x;
    aux->fiu1 = f1;
    aux->fiu2 = f2; /* actualizeaza campurile nodului */
    aux->fiu3 = f3;
    aux->fiu4 = f4;
    return aux; /* intoarce adresa nodului */
}

void distruge(TArb r) {/* functie auxiliara - distruge toate nodurile */
    if (!r)
        return;
    distruge(r->fiu1); /* distruge subarbori*/
    distruge(r->fiu2);
    distruge(r->fiu3);
    distruge(r->fiu4);
    free(r); /* distruge nodul radacina */
}

void DistrArb(TArb *a) { /* distruge toate nodurile arborelui de la adresa a */
    if (!(*a))
        return;   /* arbore deja vid */
    distruge(*a); /* distruge toate nodurile */
    *a = NULL;    /* arborele este vid */
}

int medie(int width, unsigned char **mat, int x, int y) {  // calcul medie pt culoare
    int rez = 0;
    int i = 0, j = 0;
    for (i = x; i <= x + width - 1; i++)
        for (j = y; j <= y + width - 1; j++)
            rez += mat[i][j];
    rez /= (width * width);
    return rez;
}

unsigned long long int calcMEAN(unsigned char **red, unsigned char **green, unsigned char **blue,
int width, int x, int y) {  // calcul scor
    unsigned long long int rez = 0, mred = medie(width, red, x, y);
    unsigned long long int mgreen = medie(width, green, x, y), mblue = medie(width, blue, x, y);
    int i = 0, j = 0;
    for (i = x; i <= x + width - 1; i++)
        for (j = y; j <= y + width - 1; j++)
           rez = rez + ((mred - red[i][j]) * (mred - red[i][j]) +
             (mgreen - green[i][j]) * (mgreen - green[i][j]) +
             (mblue - blue[i][j]) * (mblue - blue[i][j]));
    rez = rez / (3 * width * width);
    return rez;
}

int nrfrunze(TArb r) {  // numarul de frunze
    int k = 0;
    if (r == NULL)
        return 0;
    if (r->fiu1 == NULL && r->fiu2 == NULL && r->fiu3 == NULL && r->fiu4 == NULL)
        k++;
    k += nrfrunze(r->fiu1);
    k += nrfrunze(r->fiu2);
    k += nrfrunze(r->fiu3);
    k += nrfrunze(r->fiu4);
    return k;
}

int max_of_four(int a, int b, int c, int d) {  // max 4 nr
    int max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;
    if (d > max)
        max = d;
    return max;
}

int nrniv(TArb r) { /* numar niveluri (0 pentru arbore vid) */
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
    if (!r)
        return 0;
    n1 = nrniv(r->fiu1);
    n2 = nrniv(r->fiu2);
    n3 = nrniv(r->fiu3);
    n4 = nrniv(r->fiu4);
    return 1 + max_of_four(n1, n2, n3, n4);
}

int min_of_four(int a, int b, int c, int d) {  // min 4 nr
    int min = a;
    if (b < min)
        min = b;
    if (c > min)
        min = c;
    if (d > min)
        min = d;
    return min;
}

int detniv(TArb r, int niv, int *niv_minim) {  // nivelul primei frunze
    if (r == NULL)
        return -1;
    if (r->fiu1 == NULL && r->fiu2 == NULL && r->fiu3 == NULL && r->fiu4 == NULL) {
        if (niv < *niv_minim)
            *niv_minim = niv;
        return niv;
    }
    int n1 = detniv(r->fiu1, niv + 1, niv_minim);
    int n2 = detniv(r->fiu2, niv + 1, niv_minim);
    int n3 = detniv(r->fiu3, niv + 1, niv_minim);
    int n4 = detniv(r->fiu4, niv + 1, niv_minim);
    return min_of_four(n1, n2, n3, n4);
}
// creare arbore de compresie
TArb divizare(unsigned char **red, unsigned char **green, unsigned char **blue, int factor, int x, int y, int size) {
    TArb arb = ConstrNod(0, NULL, NULL, NULL, NULL);
    if (calcMEAN(red, green, blue, size, x, y) <= factor) {
        arb->info = 1;
        arb->r = medie(size, red, x, y);
        arb->g = medie(size, green, x, y);
        arb->b = medie(size, blue, x, y);
    } else {
        arb->fiu1 = divizare(red, green, blue, factor, x, y, size / 2);
        arb->fiu2 = divizare(red, green, blue, factor, x, y + size / 2, size / 2);
        arb->fiu3 = divizare(red, green, blue, factor, x + size / 2, y + size / 2, size / 2);
        arb->fiu4 = divizare(red, green, blue, factor, x + size / 2, y, size / 2);
    }
    return arb;
}

void noduriniv(TArb arb, int niv, int niv_cautat, FILE *out) {  // scriere noduri de pe un nivel
    if (arb == NULL)
        return;
    if (niv == niv_cautat) {
        fwrite(&arb->info, sizeof(unsigned char), 1, out);
        if (arb->info == 1) {
            fwrite(&arb->r, sizeof(unsigned char), 1, out);
            fwrite(&arb->g, sizeof(unsigned char), 1, out);
            fwrite(&arb->b, sizeof(unsigned char), 1, out);
        }
    } else {
        noduriniv(arb->fiu1, niv + 1, niv_cautat, out);
        noduriniv(arb->fiu2, niv + 1, niv_cautat, out);
        noduriniv(arb->fiu3, niv + 1, niv_cautat, out);
        noduriniv(arb->fiu4, niv + 1, niv_cautat, out);
    }
}
