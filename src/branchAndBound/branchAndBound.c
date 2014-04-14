#include <stdio.h>
#include <stdlib.h>
#include <graphe.h>
#include <branchandbound.h>
#include <brutForce.h>

/**
 * \struct arrgt
 * \brief Objet Arrangement
 *
 *  Structure stockant tous les arrangements possibles d'une suite de chiffres
 */
typedef struct arrgt1 {
	int n,    // Le nombre de chiffres differents
	    p,    // le nombre de chiffres dans un arrangement
	    anp,  // Nombre d'arrangement
	    pos,  // Pointeur pour parcourir les arrangement
	    **tab; // tableau de "anp" ligne, chaque ligne contient un arrangement
} arrgt1;

/**
 * \fn void recopierTableau(int *t1, int * t2, int taille)
 * \brief Recopie un Tableau dans un autre
 *
 * \param t1 Tableau source
 * \param t2 Tableau destination
 * \param taille le nombre de case à recopier, ou la taille min des tableaux
 * \return void
 */

void recopierTableau1(int *t1, int * t2, int taille){
  int i;
  for(i=0 ; i < taille; i++)
    t2[i] = t1[i];
}

/**
 * \fn double distanceTrajet(int * tab, Graphe g)
 * \brief Calcule la longueur d'un trajet à partir d'un tableau de ville
 *
 * \param tab tableau de villes
 * \param g Graphe
 * \return distance total parcouru
 */

double distanceTrajet2(int * tab, Graphe g){
  int nbVille = getNombreSommets(g)+1;
  int  i;
  double distance = 0;
  for(i=0; i<nbVille; i++)//-1
    distance += sommetsDistance(tab[i],tab[i+1],g);
  
  return distance;
}

double distanceTrajet1(int * tab, Graphe g, double distanceTrajetCourt){
  int nbVille = getNombreSommets(g)+1;
  int  i;
  double distance = 0;
  for(i=0; i<nbVille; i++){//-1
    if (distance>=distanceTrajetCourt)
      return distanceTrajetCourt;
    distance += sommetsDistance(tab[i],tab[i+1],g);
  }
  return distance;
}

/**
 * \fn void arrangements(arrgt *arr, int k, int *L, int *t)
 * \brief Calcule tous les arrangements possibles et les stocke dans la structure arrgt
 *
 * \param arr Référence vers une structure arrgt
 * \param k contient la taille max d'un arrangement
 * \param L contient les arrangements en cours de création
 * \param t contient l'ensemble des entiers utilisé dans les arrangements
 * \return void
 */

void arrangements1(arrgt1 *arr, int k, int *L, int *t){
  int n = arr->n, p = arr->p, i, j, j1, t2[n];
  
  if(k==p){
    arr->tab[arr->pos] = (int *)malloc(p*sizeof(int));
    for(i=0;i<p;i++) arr->tab[arr->pos][i] = L[i];
    arr->pos++;
    return;
  }
  for(i=0;i<n-k;i++){
    L[k] = t[i];
    for(j=0, j1=0;j<n-k;j++) {
      if(j != i) {
	t2[j1] = t[j];
	j1++;
      }
    }
    arrangements(arr, k+1, L, t2);
  }
}

/**
 * \fn void brutForce(Graphe g, int villeDep)
 * \brief Calcule tous les arrangements puis choisit l arrangement le plus court en prenant compte du retour
 *
 * \param g Graphe
 * \param villeDep ville de depart
 * \return void
 */
void branchAndBound(Graphe g, int villeDep){
  double distanceTrajetCourt;
  int n, p, i, j, anp, *L, *t,ind;
  arrgt1 * arr = (arrgt1 *)malloc(sizeof(arrgt1));

  int nbVille = getNombreSommets(g);
  n = nbVille-1;
  p = nbVille-1;
  for(i=n , j=0, anp=1 ; i > n-p ; i--, j++)//calcul du nombre d'arrangements
    anp *= i;
 
  arr->n = n;
  arr->p = p;
  arr->anp = anp;
  arr->pos = 0;
  arr->tab = (int **)malloc(anp * sizeof(int *));

  //Initialisation des params
  L = (int *) malloc(p*sizeof(int));
  t = (int *) malloc(n*sizeof(int));
  for(i=0,ind=0;i<n;i++,ind++){
    if(i == villeDep)
      ind++;
    t[i] = ind;//Ensemble des chiffres dans les arrangements
  }
  arrangements1(arr, 0, L, t);

  //initialisation du trajetCourt
  int * trajet = malloc(sizeof(int)*nbVille+1);//retour +1
  int * trajetCourt = malloc(sizeof(int)*nbVille+1);
  recopierTableau1(arr->tab[0], trajetCourt+1, nbVille-1);
  trajetCourt[nbVille] = villeDep;//retour
  trajetCourt[0] = villeDep;//allé

  for(i=0;i<arr->anp;i++){
      recopierTableau1(arr->tab[i], trajet+1,nbVille-1);
      trajet[nbVille] = villeDep;//retour toujours
      trajet[0] = villeDep;//allé toujours
      distanceTrajetCourt=distanceTrajet(trajetCourt,g);
	if(distanceTrajet1(trajet,g, distanceTrajetCourt) < distanceTrajet1(trajetCourt,g, distanceTrajetCourt))
	  recopierTableau1(trajet,trajetCourt,nbVille+1);
  }
  for(j=0;j<nbVille+1;j++) {
    printf("%d ",trajetCourt[j]);
  }
  printf("\nDistance parcouru : %f\n",distanceTrajet(trajetCourt,g));

  free(L);
  free(t);
  for(i=0;i<arr->anp;i++)
    free(arr->tab[i]);
  free(arr->tab);
  free(arr);

  free(trajet);
  free(trajetCourt);

}

