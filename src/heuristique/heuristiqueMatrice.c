
/**
 * \file brutForce.c
 * \brief Toutes les fonctions utile à l'heuristique
 * \author Ghislain Hudry
 * \version 0.1
 * \date 11 Mars 2014
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <matrice.h>
#include <heuristique.h>



/**
 * \fn bool parcouru(int ville, int * trajet, int ind, Matrice m)
 * \brief Recherche si une ville est dans un tableau de villes.
 *
 * \param a la ville à vérifier
 * \param b tableau de villes
 * \param c la longueur du tableau
 * \param d la matrice M
 * \return un booléen en fonction du résultat de la recherche.
 */
bool parcouru(int ville, int * trajet, int ind, Matrice m){
  int i;

  for(i = 0; i < ind+1; i++){
    if(ville == trajet[i])
      return true;
  }
  return false;
}


/**
 * \fn int villeProche( int * trajet, int ind, Matrice m)
 * \brief Recherche la ville la plus proche d'une ville donnée dans la Matrice m.
 * \param a tableau de villes déjà parcourues
 * \param b la longueur du tableau
 * \param c la matrice M
 * \return la ville de type int la plus proche de la ville passée en paramètre.
 */

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
 villeProche;
}

/**
 * \fn void heuristiqueVille(Matrice m, int i)
 * \brief La fonction permettant de calculer le chemin heuristique à partir d'un sommet.
 * \param a la Matrice m
 * \param b le sommet i
 * \return void
 */


void heuristiqueVille(Matrice m, int i){
  double distance;
  int nbVilles = getLargeurMatrice(m);
  int * trajet = malloc(sizeof(int) * (nbVilles+1));
  int j,k;

  trajet[0] = i;
  distance = 0;
  for(j = 1; j < nbVilles; j++){
    trajet[j] = villeProche(trajet,j-1,m);
    distance += getCell(trajet[j-1],trajet[j],m);
  }
  //retour:
  trajet[nbVilles] = i;
  distance += getCell(trajet[nbVilles-1],i,m);
  
  printf("Le Trajet le plus court mesure %f\n",distance);
  for(i = 0; i < nbVilles+1; i++)
    printf("%d ",trajet[i]);
  printf("\n");

}

/**
 * \fn void heuristiqueMatrice(Matrice m
 * \brief La fonction permettant de calculer l'heuristique à partir de tous les sommets en trouvant celui le plus court.
 * \param a la Matrice m
 * \return void
 */

void heuristiqueMatrice(Matrice m){
  printf("Calcul heuristique du chemin le plus court...\n");

  double distance;
  double distanceCourt = -1;
  int nbVilles = getLargeurMatrice(m);
  int * trajet = malloc(sizeof(int) * (nbVilles+1));
  int * trajetCourt = malloc(sizeof(int) * (nbVilles+1));
  int i,j,k;


  for(i = 0; i < nbVilles; i++){
    trajet[0] = i;
    distance = 0;
    for(j = 1; j < nbVilles; j++){
      trajet[j] = villeProche(trajet,j-1,m);
      distance += getCell(trajet[j-1],trajet[j],m);
    }
    //retour:
    trajet[nbVilles] = i;
    distance += getCell(trajet[nbVilles-1],i,m);

    if(distanceCourt == -1 || distanceCourt > distance){
      for(k = 0; k < nbVilles+1; k++){
	trajetCourt[k] = trajet[k];
	//trajet[k] = 0;
      }
      distanceCourt = distance;
    }
  }
  printf("Le Trajet le plus court mesure %f\n",distanceCourt);
  for(i = 0; i < nbVilles+1; i++)
    printf("%d ",trajetCourt[i]);
  printf("\n");

  free(trajet);
  free(trajetCourt);
}
