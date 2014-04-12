#include <stdio.h>
#include <stdlib.h>
#include <graphe.h>
#include <rechercheExhaust.h>


   
/*************************************************************
*Author:  gustan jimmy                             Date: 28/03/14
*Return: si oui ou non le sommet est dans le tableau
*Param: 
 graphe g
 int sommet
 tableau parcouru
**************************************************************/


bool rechercheParcouru(int sommet,int *parcouru,Graphe g){
  int nbVilleT = getNombreSommets(g);
  int i;
  for ( i=0; i<nbVilleT; i++)
    if( parcouru[i]==sommet)
      return true;
  return false;
}



   
/*************************************************************
*Author:  gustan jimmy                             Date: 28/03/14
*Return: le chemin de sommet le plus court à partir du sommet "sommet" par recherche exhaustive
*Param: 
 graphe g
 sommet de départ "sommet"
 le comptabiliseur de sommet parcouru "depart"
 le tableau des sommets déjà parcouru "parcouru"
**************************************************************/

void rechercheExhaustRecur(Graphe g, int sommet, int* parcouru, int depart){
  /*il faut mettre en paramètre un tableau de taille u nombre de sommets, depart doit etre obligatoirement 0, le graphe g et le sommet sont quelconques */
  int nbVilleT = getNombreSommets(g);
  int i;
  int ** tab=malloc(sizeof(int*)*nbVilleT-1);
  parcouru[depart]=sommet;
  if (nbVilleT<depart) 
    return ;
  for(i=0; i<nbVilleT; i++)
    if (i!=sommet)
      if (!rechercheParcouru(i,parcouru,g))
	tab[i]=sommetsDistance(sommet,i,g);
  int fin=0;
  int mini=tab[0];
  for(i=0; i<nbVilleT-1;i++)
    if(tab[i]<mini){
      mini=tab[i];
      fin=i;
    }
  parcouru[depart+1]=fin;
  rechercheExhaustRecur(g,i,parcouru,depart+1);
  free(tab);
}
	

void retournerTab(Graphe g){
  int i;
  int * parcouru=malloc(sizeof(int)*getNombreSommets(g));
  for(i=0; i<getNombreSommets(g)-1; i++)
    parcouru[i]=-1;
  rechercheExhaustRecur( g, 0, parcouru,0);
  for(i=0; i<getNombreSommets(g)-1; i++)
    printf ("%d",parcouru[i]);
}
  
    

  
