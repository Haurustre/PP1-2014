#ifndef __MATRICE_H__
#define __MATRICE_H__

struct matrice{
  double* mat;
  int largeur;
  int tailleMat;
};

typedef struct matrice * Matrice;

Matrice initMatrice(int);

int getLargeurMatrice(Matrice);
int getTailleMatrice(Matrice);
double getCell(int, int, Matrice);
void setCell(int, int, Matrice, double);

void showMatrice(Matrice);

void deleteMatrice(Matrice);

#endif
