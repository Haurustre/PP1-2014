#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <matrice.h>
#include <heuristique.h>


/*************************************************************
*Author: Ghislain Hudry                            Date: 06/03/14
*Return: ville parcouru/ville non parcouru
*Param:  numéro sommet, trajet parcouru, indice execution, Matrice
**************************************************************/
bool parcouru(int ville, int * trajet, int ind, Matrice m){
  int i;

  for(i = 0; i < ind+1; i++){
    if(ville == trajet[i])
      return true;
  }
  return false;
}

/*************************************************************
*Author: Ghislain Hudry                            Date: 06/03/14
*Return: Renvoie la ville la plus proche de ind
*Param:  trajet, indice execution, matrice
**************************************************************/
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

/*************************************************************
*Author: Ghislain Hudry                            Date: 06/03/14
*Return: Affiche le trajet le plus court de la matrice
*Param:  Matrice
**************************************************************/
void heuristiqueMatrice(Matrice m){
  printf("Calcul heuristique du chemin le plus court...\n");

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
