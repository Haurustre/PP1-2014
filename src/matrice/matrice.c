#include <matrice.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void afficherMatriceInt(Matrice m, char * ret){
  ret[0] = '\0';
  sprintf(ret,"Matrice %d x %d :\n",m->largeur,m->largeur);
  int i,j=0;
  for(i = 0; i < m->tailleMat; i++){
    sprintf(ret,"%s %2d",ret,(int)m->mat[i]);
    j++;
    if((m->largeur) == j){
      strcat(ret,"\n");
      j=0;
    }
  }
}

/*******************************************************
 *Auteur: Ghislain Hudry                Date:06/03/14  *
 *Charge une Matrice en fonction du test fichier ouvert*
 *******************************************************/
Matrice chargerMatrice(char * path){
  Matrice m;
  char var[1000];
  int * tailleMatrice = malloc(sizeof(int));
  int i;
  float *valIndiceMatrice = malloc(sizeof(float));

  //printf("Ouverture du fichier %s\n",path);
  FILE * tsp = fopen(path,"r");

  if(tsp == NULL){
    printf(" erreur %d\n",errno);
    if(errno == ENOENT)
      printf("Le fichier n'existe pas !\n");
    else
      printf("Erreur inconnue\n");
  }
  else{
    //printf("Creation de la matrice... ");
    fscanf(tsp,"%s",var);
    while(strcmp(var, "DIMENSION:") != 0 && !feof(tsp)){
      fscanf(tsp,"%s",var);
    }
    fscanf(tsp,"%d",tailleMatrice);
    m = initMatrice(*tailleMatrice);

    while(strcmp(var, "EDGE_WEIGHT_SECTION") != 0 && !feof(tsp)){
      fscanf(tsp,"%s",var);
    }
    if( ! feof(tsp)){
      for(i=0; i< ((*tailleMatrice) * (*tailleMatrice)); i++){
	fscanf(tsp,"%f",valIndiceMatrice);
	setIndMatrice(i,m,*valIndiceMatrice);
      }
    
    }
    else
      printf("Erreur lors de la lecture du fichier, DIMENSION doit etre specifie avant EDGE_WEIGHT_SECTION\n");
    fclose(tsp);
    //printf(" fait\n");
  }
  free(valIndiceMatrice);
  free(tailleMatrice);
  return m;
}

bool matriceSymetrique(Matrice m){
  int y,x;
  for(x = 0; x < m->largeur ; x++){
    for(y = x; y < m->largeur ; y++){
      if(x == y && m->mat[y*(m->largeur)+x]!=0)
        return false;//diagonale pas a zero
      if(m->mat[y*(m->largeur)+x] != m->mat[x*(m->largeur)+y])
	return false;
    }
  }
  return true;
}

bool matricePlanaire(Matrice m){
  int y,x,z;
  for(x = 0; x < m->largeur ; x++){
    for(y = 0; y < m->largeur ; y++){
      if(x != y){
	for(z = 0; z < m->largeur; z++){
	  if(z != y){
	    if( m->mat[y*(m->largeur)+x] >  m->mat[y*(m->largeur)+z]
		+ m->mat[z*(m->largeur)+x])
	      return false;
	    
	  }
	}
      }
    }
  }
  return true;
}

void deleteMatrice(Matrice m){
  free(m->mat);
  free(m);
}
