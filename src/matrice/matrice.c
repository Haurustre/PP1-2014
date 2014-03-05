#include <matrice.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct matrice{
  double* mat;
  int largeur;
  int tailleMat;
};

typedef struct matrice * Matrice;

int getIndiceXY(int x, int y, Matrice m){
  int ind = y * (m->largeur) + x;
  assert(ind >= 0 && ind < m->tailleMat); 
  return(ind);
}

Matrice initMatrice(int largeur){
  Matrice m = malloc(sizeof(struct matrice));
  assert( m != NULL);
  m->tailleMat = largeur*largeur;
  m->largeur = largeur;
  m->mat = malloc(sizeof(double)*m->tailleMat);
  assert(m->mat != NULL);
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

void setIndMatrice(int ind, Matrice m, double val){
  assert(ind > -1 && ind < m->tailleMat);
  m->mat[ind] = val;
}

void afficherMatrice(Matrice m){
  printf("Matrice %d x %d :\n",m->largeur,m->largeur);
  int i,j=0;
  for(i = 0; i < m->tailleMat; i++){
    printf(" %f",m->mat[i]);
    j++;
    if((m->largeur) == j){
      printf("\n");
      j=0;
    }
  }
}

void afficherMatriceInt(Matrice m){
  printf("Matrice %d x %d :\n",m->largeur,m->largeur);
  int i,j=0;
  for(i = 0; i < m->tailleMat; i++){
    printf(" %d",(int)m->mat[i]);
    j++;
    if((m->largeur) == j){
      printf("\n");
      j=0;
    }
  }
}

void deleteMatrice(Matrice m){
  free(m->mat);
  free(m);
}
