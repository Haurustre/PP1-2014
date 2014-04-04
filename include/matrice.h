#ifndef __MATRICE_H__
#define __MATRICE_H__

#include <errno.h>
#include <stdbool.h>

struct matrice;

typedef struct matrice * Matrice;

Matrice initMatrice(int);

int getLargeurMatrice(Matrice);
int getTailleMatrice(Matrice);

double getCell(int, int, Matrice);
void setCell(int, int, Matrice, double);

void setIndMatrice(int, Matrice, double);

void afficherMatrice(Matrice);
void afficherMatriceInt(Matrice, char*);

Matrice chargerMatrice(char * path);

bool matriceSymetrique(Matrice);
bool matricePlanaire(Matrice);

void deleteMatrice(Matrice);

#endif
