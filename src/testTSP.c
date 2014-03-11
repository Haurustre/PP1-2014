#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <heuristique.h>

Matrice usage(int argc, char * argv[]){
  Matrice m;
  if(argc == 1){
    printf("Utilisation de la matrice par défaut...\n");
    m = chargerMatrice("res/exemple14.tsp");
  }
  else if(argc == 2){
    printf("Utilisation de la matrice %s\n",argv[1]);
    m = chargerMatrice(argv[1]);
  }
  else{
    printf("Usage: testTSP (utilisation matrice par défaut)\n");
    printf("       testTSP [chemin vers le fichier tsp]\n");
  }
  return m;
}

int main(int argc, char * argv[]){
  Matrice m = usage(argc,argv);

  afficherMatriceInt(m);
  heuristiqueMatrice(m);
  deleteMatrice(m);

  return 0;
}
