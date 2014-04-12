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
/*
void rechercheExhaustRecur(Graphe g, int sommet, int* parcouru, int depart){
  /*il faut mettre en paramètre un tableau de taille u nombre de sommets, depart doit etre obligatoirement 0, le graphe g et le sommet sont quelconques 
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
*/





int echanger(int premierSommet, int secondSommet, int * tableau, int longueurTab){
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
    

  
