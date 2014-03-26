#include <graphe.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

bool toutVisite(bool * t, int taille){
  int i;
  for(i = 0; i < taille; i++)
    if(t[i] == false)
      return false;
  return true;
}
/**************************************************************
 *Auteur: Ghislain Hudry                       Date:12/03/14
 *Param: Graphe g
 *Affiche le chemin le plus court trouvé par L'algo de Prim
 *(avec tri bulle).
 **************************************************************/
void calculerMST(Graphe g){
  printf("Calcule approximatif du chemin le plus court (Prim /Mst)...\n");
  srand(time(NULL));
  int nbVilleT = getNombreSommets(g);
  int nbArcsT;
  Arc * arcsCroissants = getArcs(&nbArcsT,g);
  Arc * chemin = malloc(sizeof(Arc)*(nbVilleT-1));
  Arc * minChemin = malloc(sizeof(Arc)*(nbVilleT-1));

  int i;
  Arc arcTmp;
  bool echange = true;
  //tri Bulle du tableau d'Arc de facon croissante
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
  for(j=0; j<nbVilleT; j++){//depart de l'algo depuis chaque ville ( J )
    for(i = 0; i < nbVilleT; i++)//remise a zero, aucune ville visité...
      ville[i] = false;
    ville[j] = true;// ...excepté celle de depart
    villeActuel = j;//;;placement du "curseur" de ville
    distance = 0;
    nbVilleChemin = 0;
    while(!toutVisite(ville,nbVilleT)){//Recherche du trajet le plus court partant de la ville J
      for(i=0;i < nbArcsT-1;i++){ //On parcourt le tableau d'arc trié en ordre croissant
	if(getSommetA(arcsCroissants[i]) ==  villeActuel){ //le premier arc trouvé correspondant est alors retenu...
	  if(!ville[getSommetB(arcsCroissants[i])]){//...Cest a dire qui va de la ville actuel a une ville non visité

	    villeActuel = getSommetB(arcsCroissants[i]);//le "curseur" ville devient la nouvelle ville
	    chemin[nbVilleChemin++] = arcsCroissants[i];//on ajoute l arc au chemin
	    distance += getDistance(arcsCroissants[i]);//on ajoute a la distance du chemin
	    ville[villeActuel] = true;
	    break;//Quand on a trouvé un Arc il faut recommencer le parcourt du tableau d arc trié depuis le debut
	    //donc un break pour sortir de la boucle for
	  }//if
	}//if
      }//for
    }//while

    if(minDistance == -1 || minDistance > distance){//A la fin on teste si le chemin calculé est plus court que le precedent
      for(i = 0; i < (nbVilleT-1);i++)//SI oui: alors distanceMin et cheminMin prennent ces valeurs
	minChemin[i] = chemin[i];
      minDistance = distance;
    }

  }//et ainsi de suite pour chaque ville de depart




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
