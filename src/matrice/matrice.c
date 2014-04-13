/**
 * \file matrice.c
 * \brief Source de la bibliotheque matrice
 * \author Ghislain Hudry
 * \version 0.1
 * \date 18 Janvier 2014
 *
 * Structure de la Matrice
 *
 */
#include <matrice.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * \struct matrice
 * \brief Objet matrice
 * Structure permettant de créer un tableau à deux dimensions avec une largeur et une taille donnée.
 */

struct matrice{
  double* mat;
  int largeur;
  int tailleMat;
};

typedef struct matrice * Matrice;

/**
 * \fn int getIndiceXY(int x, int y, Matrice m)
 * \brief Fonction retournant la valeur des coordonnées x et y dans la matrice en paramètre.
 * \param a l'indice x
 * \param b l'indice y
 * \param c la matrice m
 * \return l'indice des coordonnées pris en paramètre.
 */

int getIndiceXY(int x, int y, Matrice m){
  int ind = y * (m->largeur) + x;
  assert(ind >= 0 && ind < m->tailleMat); 
  return(ind);
}

/**
 * \fn Matrice initMatrice(int largeur)
 * \brief Fonction d'initialisation de la matrice.
 *
 * \param a la largeur de la matrice
 * \return Instance nouvellement allouée d'un objet de type Matrice.
 */

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
/**
 * \fn int getLargeurMatrice(Matrice m)
 * \brief Fonction qui renvoie la largeur de la Matrice m.
 *
 * \param a la Matrice m
 * \return Nombre Réel de type int contenant la largeur de la Matrice.
 */

int getLargeurMatrice(Matrice m){
  return m->largeur;
}

/**
 * \fn int getTailleMatrice(Matrice m)
 * \brief Fonction qui renvoie la taille de la Matrice m.
 *
 * \param a la Matrice m
 * \return Nombre Réel de type int contenant la taille de la Matrice.
 */

int getTailleMatrice(Matrice m){
  return m->tailleMat;
}

/**
 * \fn double getCell(int x, int y, Matrice m)
 * \brief Fonction qui renvoie la cellule de la Matrice m.
 *
 * \param a la coordonnée x
 * \param b la coordonnée y
 * \param c la Matrice m
 * \return Nombre Réel de type double contenant l'indice des coordonnées mis en paramètre de la Matrice.
 */

double getCell(int x, int y, Matrice m){
  return(m->mat[getIndiceXY(x,y,m)]);
}

/**
 * \fn void setCell(int x, int y, Matrice m, double val)
 * \brief Fonction qui définie une nouvelle valeur à la cellule mise en paramètre.
 * \param a la coordonnée x
 * \param b la coordonnée y
 * \param c la Matrice m
 * \param d la nouvelle valeur
 * \return void
 */

void setCell(int x, int y, Matrice m, double val){
  m->mat[getIndiceXY(x,y,m)] = val;
}



/**
 * \fn void setIndMatrice(int ind, Matrice m, double val)
 * \brief Fonction qui définie une nouvelle valeur à l'indice mis en paramètre.
 * \param a l'indice 
 * \param b la Matrice m
 * \param c la nouvelle valeur
 * \return void
 */
void setIndMatrice(int ind, Matrice m, double val){
  assert(ind > -1 && ind < m->tailleMat);
  m->mat[ind] = val;
}


/**
 * \fn void afficherMatrice(Matrice m)
 * \brief Fonction qui affiche la Matrice avec des nombres float
 * \param a la Matrice m
 * \return void
 */


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
/**
 * \fn void afficherMatriceInt(Matrice m, char * ret)
 * \brief Fonction qui affiche la Matrice avec des nombres int
 * \param a la Matrice m
 * \param b la chaîne de caractère ret
 * \return void
 */

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

/**
 * \fn Matrice chargerMatrice(char * path)
 * \brief Fonction qui charge une Matrice à partir des fichiers personnels
 * \param a une chaîne de caractère décrivant le chemin du fichier
 * \return une Matrice m.
 */

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

/**
 * \fn bool matriceSymetrique(Matrice m)
 * \brief Fonction qui teste si une matrice est symétrique ou pas
 * \param a la Matrice m
 * \return void
 */

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

/**
 * \fn bool matricePlanaire(Matrice m)
 * \brief Fonction qui teste si une matrice est planaire ou pas
 * \param a la Matrice m
 * \return void
 */


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
