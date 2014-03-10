#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

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
  free(valIndiceMatrice);
  free(tailleMatrice);
  return m;
}
/*
bool parcouru(int * t, int taille){
  int i;
  for(i = 0; i<taille; i++){
    if(t[i] == -1)
      return false;
  }
  return true;
}

int villePlusProche(int villeTmp,int * villeSuiv, int * t, Matrice m){
  int indMin;
  int distance = getCell(villeTmp,0);
  for( i = 1; i < getLargeurMatrice(m); i++){
    if(t[i] == -1){
      if(distance < getCell(villeTmp,i,m)){
	distance = getCell(villeTmp,i,m);
        indMin = i;
      }
    }
  }
  t[indMin] = 1;
  return indMin;
}

int * heuristique(Matrice m){
  int i;
  int villeTmp, villeSuiv;
  int tailleM = getLargeurMatrice(m);
  int * tmp = malloc(sizeof(int)*getLargeurMatrice(m));
  int * parcouruVille = malloc(sizeof(int)*getLargeurMatrice(m));
  for(i =0; i < getLargeurMatrice(m) ; i++)
    parcouruVille[i] = -1;

  int * plusCourt = malloc(sizeof(int)*getLargeurMatrice(m));
  double distance = -1;
  
  for(i =0; i < tailleM ; i++){
    tmp[0] = i;
    parcouru[i] = 1;
    villeTmp = i;
    while(!parcouru(parcouruVille,tailleM)){
      tmp[villeTmp] = villePlusProche(villeTmp,villeSuiv,parcouruVille,m);
      villeTmp = villeSuiv;
    }

    if((distance == -1) || (distanceParcourt(tmp) < distance)){
      for(i =0; i < getLargeurMatrice(m) ; i++)
	plusCourt[i] = tmp[i];
      distance = distanceParcourt(plusCourt);
    }
  }
  free(tmp);
  free(parcouruVille);
  printf("meilleurs distance:%f",distance);
  return plusCourt;
}
*/
int main(){
  Matrice m = chargerMatrice();
  afficherMatriceInt(m);

  deleteMatrice(m);
  return 0;
}
