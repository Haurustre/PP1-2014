#include <graphe.h>

int main(){

  Graphe g = initGraphe(3);
  ajouterArc(0,1,0.5f,g);
  ajouterArc(0,2,0.6f,g);
  afficherGraphe(g);
  deleteGraphe(g);
  return 0;
}
