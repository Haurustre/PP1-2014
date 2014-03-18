#include <graphe.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Arc{
  int villaA, villeB;
  double poids;
};

void calculerMST(Graphe g){
  //int nbVilleT = getNombreSommets(g);
  int nbArcsT;
  Arc * arcsCroissants = getArcs(&nbArcsT,g);
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

  // Algo de prim

}
