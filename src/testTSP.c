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

bool parcouru(int ville, int * trajet, int ind, Matrice m){
  int i;

  for(i = 0; i < ind+1; i++){
    if(ville == trajet[i])
      return true;
  }
  return false;
}

int villeProche( int * trajet, int ind, Matrice m){
  double distance = -1;
  int villeProche = -1;
  int i;
  for(i = 0; i < getLargeurMatrice(m); i++){
    if(!parcouru(i,trajet,ind,m)){
      if(distance == -1 || getCell(ind,i,m)<distance){
	distance = getCell(ind,i,m);
	villeProche = i;
      }
    }  
  }
  return villeProche;
}

void heuristiqueTest(Matrice m){
  printf("Calcule heuristique du chemin le plus court...\n");

  double distance;
  double distanceCourt = -1;
  int nbVilles = getLargeurMatrice(m);
  int * trajet = malloc(sizeof(int) * nbVilles);
  int * trajetCourt = malloc(sizeof(int) * nbVilles);
  int i,j,k;
  for(i = 0; i < nbVilles; i++){
    trajet[0] = i;
    distance = 0;
    for(j = 1; j < nbVilles; j++){
      trajet[j] = villeProche(trajet,j-1,m);
      distance += getCell(trajet[j-1],trajet[j],m);
    }
    if(distanceCourt == -1 || distanceCourt > distance){
      for(k = 0; k < nbVilles; k++){
	trajetCourt[k] = trajet[k];
	trajet[k] = 0;
      }
      distanceCourt = distance;
    }
  }
  printf("Le Trajet le plus court mesure %f\n",distanceCourt);
  for(i = 0; i < nbVilles; i++)
    printf("%d ",trajetCourt[i]);
  printf("\n");

  free(trajet);
  free(trajetCourt);
}

int main(){
  Matrice m = chargerMatrice();
  afficherMatriceInt(m);
  heuristiqueTest(m);
  deleteMatrice(m);
  return 0;
}
