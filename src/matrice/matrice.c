#include "matrice.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int getIndiceXY(int x, int y, Matrice m){
  int ind = y * (m->largeur) + x;
  assert(ind >= 0 && ind < m->tailleMat); 
  return(ind);
}

Matrice initMatrice(int largeur, int hauteur){
  Matrice m = malloc(sizeof(struct matrice));
  m->tailleMat = largeur*largeur;
  m->largeur = largeur;
  m->mat = malloc(sizeof(int)*m->tailleMat);
  int i;
  for(i = 0; i < m->tailleMat; i++)
    m->mat[i] = 0;

  return m;
}

int getLargeurMatrice(Matrice m){
  return m->largeur;
}

int getTailleMatrice(Matrice m){
  return m->tailleMat;
}

double getCell(int x, int y, Matrice m){
  return(m->mat[getIndiceXY(x,y,m)]);
}

void setCell(int x, int y, Matrice m, double val){
  m->mat[getIndiceXY(x,y,m)] = val;
}

void showMatrice(Matrice m){
  printf("Matrice %d x %d :\n",m->largeur,m->largeur);
  int i;
  for(i = 0; i < m->tailleMat; i++){
    printf(" %4f",m->mat[i]);
    if(i%(m->largeur) == 1)
      printf("\n");
  }
}

void deleteMatrice(Matrice m){
  free(m->mat);
  free(m);
}
