#ifndef __MATRICE_H__
#define __MATRICE_H__

struct matrice;

typedef struct matrice * Matrice;

Matrice initMatrice(int);

int getLargeurMatrice(Matrice);
int getTailleMatrice(Matrice);
double getCell(int, int, Matrice);
void setCell(int, int, Matrice, double);

void afficherMatrice(Matrice);
void afficherMatriceInt(Matrice);

void deleteMatrice(Matrice);

#endif
