#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <matrice.h>
#include <graphe.h>
#include "../../include/heuristique.c"


/*************************************************************
*Author:  gustan jimmy                             Date: 04/03/14
*Return: distance entre 2 sommets passé en param
*Param:  matrice m,  sommet A et sommet B
**************************************************************/

double sommetsDistanceMatrice(int sommetA, int sommetB, matrice m){
  return getCell(sommetA, sommetB, m);
}

/*************************************************************
*Author:  gustan jimmy                             Date: 05/03/14
*Return: sommet ayant la plus petite distance avec celui passé en param non parcouru
*Param:  sommet de départ, matrice m , tableau des sommets parcouru
**************************************************************/
int sommetPlusProche(int sommetDepart, matrice m, int *parcouru){
  int sommetDistanceMin;
  if (sommetDepart==getTailleMatrice(m)-1)
    sommetDistanceMin=sommetsDistanceMatrice(sommetDepart, sommetDepart-1,m);
  else
    sommetDistanceMin=sommetsDistanceMatrice(sommetDepart,sommetDepart+1,m);
  for (int i=0; i<getTailleMatrice(m); i++){
    if (sommetDepart!=i)
      if (sommetsDistanceMatrice(sommetDepart, i, m)<sommetDistanceMin)
	if (parcouru[i]==-1){
	 sommetDistanceMin =sommetsDistanceMatrice(sommetDepart, i, m);
  }
  return sommetDistanceMin;
  }
}

/*************************************************************
*Author:  gustan jimmy                             Date: 05/03/14
*Return: tableau ayant chaque indice le prochain sommet à distance minimum non parcouru
*Param:  matrice m et le sommet de départ
**************************************************************/


int *  heuristique(matrice m, sommetDepart){
  int j=0;
  int tailleM=getTailleMatrice(m)
  int * parcouru= malloc(tailleM*sizeof(*int));
  for (int i=0; i< tailleM; i++)
    parcouru[i]=-1;
  while( j<= tailleM){
    parcouru[sommetDepart]=sommetPlusProche(sommetDepart, m, parcouru);
    sommetDepart=parcouru[sommetDepart]
    j++;
  }
  return parcouru;
      
}
/*************************************************************
*Author:  gustan jimmy                             Date: 05/03/14
*Return:  rien
*Param:  tableau des sommets parcouru
**************************************************************/

void deleteParcouru( int * parcouru){ 
  free(parcouru);
}
  
			      
		 
  
  
  






