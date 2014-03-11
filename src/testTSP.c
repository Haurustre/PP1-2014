#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <heuristique.h>

int main(){
  Matrice m = chargerMatrice("res/exemple14.tsp");
  afficherMatriceInt(m);
  heuristiqueMatrice(m);
  deleteMatrice(m);
  return 0;
}
