/**
 * \file recherchExhaust.c
 *\author:  gustan jimmy                             
 *\date: 28/03/14
 *\brief Echange la valeur des deux indices dans le tableau pris en paramètre, tout en gardant la même valeur sur l'indice 0 et le dernier.
 *\param a  l'indice 1
 *\param b l'indice 2
 *\param c le tableau
 *\param d la longueur du tableau
*/
#include <stdio.h>
#include <stdlib.h>
#include <graphe.h>
#include <rechercheExhaust.h>




void echanger(int premierSommet, int secondSommet, int * tableau, int longueurTab){
  if(premierSommet==0){
    int tmp=tableau[premierSommet];
    tableau[premierSommet]= tableau[secondSommet];
    tableau[secondSommet]= tmp;
    tableau[longueurTab] = tableau[0];
  }
  int tmp=tableau[premierSommet];
  tableau[premierSommet]= tableau[secondSommet];
  tableau[secondSommet]= tmp;
}

int sommeTab(int * tableau, int longueurTab, Graphe g){
  int i;
  int somme=0;
  for(i=0; i<longueurTab-1; i++)
    somme+=sommetsDistance(i, i+1, g);
  return somme;
}

int * sommePlusPetite(int * sommets1, int *sommets2, int longueurTab, Graphe g){
  int i, somme1, somme2;
  for(i=0; i<longueurTab; i++){
    somme1=sommeTab(sommets1, longueurTab, g);
    somme2=sommeTab(sommets2, longueurTab, g);
  }
  if (somme1< somme2)
    return sommets1;
  return sommets2;
}
      
int* BruteForce(Graphe g, int * sommets, int sommetDepart){
  int i, somme1, somme2;
  int * sommets1=malloc(sizeof(int*)*getNombreSommets(g)+1);
  for(i=0; i<=getNombreSommets(g); i++)
    sommets1[i]=sommets[i];
//sauvegarde de l'ordre des sommets mis en paramètre
  somme1=sommeTab(sommets, getNombreSommets(g), g);
  if (getNombreSommets(g)==sommetDepart)
    return sommets;
  for(i=0; i<getNombreSommets(g)-1; i++)
    if (sommetDepart!=i){
      echanger(sommetDepart, i, sommets,getNombreSommets(g));
      somme2=sommeTab(sommets,getNombreSommets(g), g);
      sommets=sommePlusPetite(sommets, sommets1,getNombreSommets(g), g);
    }
  return BruteForce(g,sommets,sommetDepart+1) ;
  free( sommets1);
}
int * BruteForceVersion2(Graphe G, int * sommets){
  
  int i, somme1, somme2, nombreVille, compteurDeVille;
  compteurDeVille = 0; // définit à combien de ville on en est pour le tour de boucle mais aussi quel ville est sélectionné.
  nombreVille = getNombreSommets(g);
  int * sommets1=malloc(sizeof(int*)*nombreVille+1);
  for(i=0; i<=nombreVille(g);i++)
    sommets1[i]=sommets[i];
  somme1=sommeTab(sommets,nombreVille, g);
  while (compteurDeVille<nombreVille){
    for(i=0; i<nombreVille; i++)
      if (compteurDeVile!=i){
	echanger( compteurDeville, i, sommets, nombreVille );
	somme2=sommeTab(sommets, nombreVille, g);
	sommets=sommePlusPetite(sommets, sommets1, nombreVille, g);
      }
    compteurDeVille++;
  }
  free(sommets1);
  return sommets;
}
    

int * retournerTab(Graphe g){
  int i;
  int * tableauDepart=malloc(sizeof(int)*getNombreSommets(g)+1);
  for(i=0; i<getNombreSommets(g); i++)
    tableauDepart[i]=i;
  tableauDepart[getNombreSommets(g)-1]= 0;
  BruteForce(g, tableauDepart,0);
  for (i=0; i<getNombreSommets(g); i++)
    printf ("%d\n",tableauDepart[i]);
  free (tableauDepart);
}
    

  
