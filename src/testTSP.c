#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

Matrice chargerMatrice(){
  Matrice m;
  char var[1000];
  int * tailleMatrice;
  int i;
  float *valIndiceMatrice;

  printf("Ouverture du fichier tsp...\n");
  FILE * tsp = fopen("../res/exemple10.tsp","r");
  if(tsp == NULL)
    tsp = fopen("res/exemple10.tsp","r");
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

  return m;
}

int main(){
  Matrice m = chargerMatrice();
  afficherMatriceInt(m);

  deleteMatrice(m);
  return 0;
}
