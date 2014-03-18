#include <graphe.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct arc{
  int sommetA;
  int sommetB;
  double distance;
};
bool toutVisite(bool * t, int taille){
  int i;
  for(i = 0; i < taille; i++)
    if(t[i] == false)
      return false;
  return true;
}

void calculerMST(Graphe g){
  printf("Calcule approximatif du chemin le plus court (Prim /Mst)...\n");
  srand(time(NULL));
  int nbVilleT = getNombreSommets(g);
  int nbArcsT;
  Arc * arcsCroissants = getArcs(&nbArcsT,g);
  Arc * chemin = malloc(sizeof(struct arc)*(nbVilleT-1));
  Arc * minChemin = malloc(sizeof(struct arc)*(nbVilleT-1));

  int i;
  Arc arcTmp;
  bool echange = true;
  //tri Bulle
  while(echange){
    echange = false;
    for(i=0;i < nbArcsT-1;i++){
      if(getDistance(arcsCroissants[i]) > getDistance(arcsCroissants[i+1])){
	echange = true;
	arcTmp = arcsCroissants[i];
	arcsCroissants[i] = arcsCroissants[i+1];
	arcsCroissants[i+1] = arcTmp;
      }
    }
  }

  bool * ville = malloc(sizeof(bool) * nbVilleT );
  double minDistance = -1;
  int j;
  int villeActuel;
  double distance;
  int nbVilleChemin = 0;
  for(j=0; j<nbVilleT; j++){//depart depuis chaque ville
    for(i = 0; i < nbVilleT; i++)//remise a zero
      ville[i] = false;
    ville[j] = true;
    villeActuel = j;
    distance = 0;
    nbVilleChemin = 0;
    while(!toutVisite(ville,nbVilleT)){//plus court ville J
      for(i=0;i < nbArcsT-1;i++){
	if(getSommetA(arcsCroissants[i]) ==  villeActuel){
	  if(!ville[getSommetB(arcsCroissants[i])]){

	    villeActuel = getSommetB(arcsCroissants[i]);
	    chemin[nbVilleChemin++] = arcsCroissants[i];
	    distance += getDistance(arcsCroissants[i]);
	    ville[villeActuel] = true;
	    break;//sortir du for pour recommencer à zero
	  }//if
	}//if
      }//for
    }//while

    if(minDistance == -1 || minDistance > distance){
      for(i = 0; i < (nbVilleT-1);i++)
	minChemin[i] = chemin[i];
      minDistance = distance;
    }

  }




  printf("Le Trajet le plus court mesure %f\n",minDistance);
  for(i=0; i<(nbVilleChemin); i++){//affiche les sommets -1
    printf("%d ",getSommetA(minChemin[i]));
    distance = i;
  }
  printf("%d ",getSommetB(minChemin[(int)distance]));
  printf("\n");//affiche dernier sommet
  // Algo de prim

  free(ville);
  free(arcsCroissants);
  free(chemin);
  free(minChemin);
}
