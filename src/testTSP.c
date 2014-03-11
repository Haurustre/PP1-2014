#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <heuristique.h>

/*******************************************************
 *Auteur: Ghislain Hudry                Date:06/03/14  *
 *Charge une Matrice en fonction du test fichier ouvert*
 *******************************************************/
Matrice chargerMatrice(){
  Matrice m;
  char var[1000];
  int * tailleMatrice = malloc(sizeof(int));
  int i;
  float *valIndiceMatrice = malloc(sizeof(float));

  printf("Ouverture du fichier tsp...\n");
  FILE * tsp = fopen("../res/exemple14.tsp","r");
  if(tsp == NULL)
    tsp = fopen("res/exemple14.tsp","r");
  if(tsp == NULL){
    printf(" erreur %d\n",errno);
    if(errno == ENOENT)
      printf("Le fichier n'existe pas !\n");
    else
      printf("Erreur inconnue\n");
  }
  else{
    printf("Creation de la matrice...\n");
    fscanf(tsp,"%s %s",var,var);
    fscanf(tsp,"%s %s",var,var);
    fscanf(tsp,"%s %d",var,tailleMatrice);
    m = initMatrice(*tailleMatrice);
    fscanf(tsp,"%s %s",var,var);
    fscanf(tsp,"%s %s",var,var);
    fscanf(tsp,"%s %s",var,var);
    fscanf(tsp,"%s",var);
    
    for(i=0; i< ((*tailleMatrice) * (*tailleMatrice)); i++){
      fscanf(tsp,"%f",valIndiceMatrice);
      setIndMatrice(i,m,*valIndiceMatrice);
    }

    fclose(tsp);
    printf(" fait\n");
  }
  free(valIndiceMatrice);
  free(tailleMatrice);
  return m;
}

int main(){
  Matrice m = chargerMatrice();
  afficherMatriceInt(m);
  heuristiqueMatrice(m);
  deleteMatrice(m);
  return 0;
}
