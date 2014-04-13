
/**
 * \file brutForce.c
 * \brief Toutes les fonctions utiles pour le minimum spanning tree 
 * \author Ghislain Hudry
 * \version 0.1
 * \date 18 Mars 2014
 *
 *
 */

#include <graphe.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/**
 * \fn bool toutVisite(bool * t, int taille)
 * \brief La fonction vérifie si le tableau de type bool contient uniquement que des "true" ou pas
 * \param a le tableau de type bool
 * \param b la taille du tableau
 * \return un boolean en fonction de la recherche.
 */
bool toutVisite(bool * t, int taille){
  int i;
  for(i = 0; i < taille; i++)
    if(t[i] == false)
      return false;
  return true;
}

/**
 * \fn void calculerMST(Graphe g)
 * \brief La fonction qui calcule le minimum spanning tree dans le Graphe g en commençant par tous les sommets puis trouvant le meilleure 
 * \param a le Graphe g
 * \return void
 */

void calculerMST(Graphe g){
  printf("Calcule approximatif du chemin le plus court (Prim /Mst)...\n");
  int nbVilleT = getNombreSommets(g);
  int nbArcsT;
  Arc * arcsCroissants = getArcs(&nbArcsT,g);
  Arc * chemin = malloc(sizeof(Arc)*(nbVilleT));
  Arc * minChemin = malloc(sizeof(Arc)*(nbVilleT));

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

    //retour:
    distance+=sommetsDistance(j,villeActuel,g);
    chemin[nbVilleT-1] = getArc(villeActuel,j,g);

    
    if(minDistance == -1 || minDistance > distance){//A la fin on teste si le chemin calculé est plus court que le precedent
      for(i = 0; i < (nbVilleT);i++)//SI oui: alors distanceMin et cheminMin prennent ces valeurs
	minChemin[i] = chemin[i];
      minDistance = distance;
    }

  }//et ainsi de suite pour chaque ville de depart




  printf("Le Trajet le plus court mesure %f\n",minDistance);
  for(i=0; i<(nbVilleT); i++){//affiche les sommets -1
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

/**
 * \fn void calculerMSTVille(Graphe g,int ind)
 * \brief  La fonction qui calcule le minimum spanning tree à partir d'un sommet uniquement
 * \param a le Graphe g
 * \param b le sommet
 * \return void
 */

void calculerMSTVille(Graphe g,int ind){
  printf("Calcule approximatif du chemin le plus court (Prim /Mst)...\n");
  int nbVilleT = getNombreSommets(g);
  int nbArcsT;
  Arc * arcsCroissants = getArcs(&nbArcsT,g);
  Arc * chemin = malloc(sizeof(Arc)*(nbVilleT));

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
  int j = ind;
  int villeActuel;
  double distance;
  int nbVilleChemin = 0;
 
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

    //retour:
    distance+=sommetsDistance(j,villeActuel,g);
    chemin[nbVilleT-1] = getArc(villeActuel,j,g);


  printf("Le Trajet le plus court mesure %f\n",distance);
  for(i=0; i<(nbVilleT); i++){//affiche les sommets -1
    printf("%d ",getSommetA(chemin[i]));
    distance = i;
  }
  printf("%d ",getSommetB(chemin[(int)distance]));
  printf("\n");//affiche dernier sommet
  // Algo de prim

  free(ville);
  free(arcsCroissants);
  free(chemin);
}
