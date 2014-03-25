#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <arbrePlanaire.h>



struct arbrePlainaire{
  arbre pere;
  arbre premierfilsGauche;
  arbre* frere;
  int nombreFrere;
};


arbrePlanaire initArbrePlanaire(arbrePlanaire arbre){
  ArbrePlainaire pere = malloc(sizeof(struct arbrePlainaire));
  int * 
  assert(pere!= NULL);
  arbre-> pere = arbre;
  arbre-> premierFilsGauche = NULL;
  arbre-> frere = malloc(sizeof(arbre*));
  assert(arbre -> frere!=NULL);
  arbre*-> frere[0]=NULL;
  arbre->nombreFrere = 1;   
  return pere;
  }

void ajouterPremierFilsGauche(arbrePlanaire arbre){
  arbre->premierFilsGauche = arbre;
}

void ajouterFrere(arbrePlanaire frere){
  bool ajouter = false;
  int i=arbre->nombreFrere;
  while (ajouter==false){
    if (arbre* ->frere[i]==NULL){
      arbre*-> frere[i] = frere;
      arbre*->frere = realloc(arbre*->frere, ((arbre*->nombreFrere)+1)*sizeof(arbre *));
      arbre*-> frere[(arbre*->nombreFrere)+1]=NULL;
      arbre->nombreFrere++;
      ajouter= true;
    }
    i++;
  }
}

arbrePlanaire trouverFrere(int quelFrere){
  assert(arbre* -> frere [quelFrere]!= NULL);
  return arbre*-> frere[quelFrere];
}

void enleverFrere(int quelFrere){
  assert(arbre* -> frere [quelFrere]!= NULL);
  arbre* -> frere [quelFrere]= NULL;
}

void detruireArbrePlanaire(arbrePlanaire arbre){
  free(arbre*->frere);
  free(arbrePlanaire);
}


  
  






    
  
  
  
    
			   
