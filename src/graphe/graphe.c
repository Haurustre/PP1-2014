#include "graphe.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

Graphe initGraphe(int nombreSommet){
  Graphe g = malloc(sizeof(struct graphe));
  g->nbS = nombreSommet;
  
  g->adjs = malloc(sizeof(struct Adj) * g->nbS);
  int i;
  for(i = 0; i < g->nbS; i++){
    g->adjs[i].arcs = malloc(sizeof(struct arc)* g->nbS);
    g->adjs[i].nbAdj = 0;
  }

  return g;
}

int getNombreSommets(Graphe g){
  return g->nbS;
}

bool sommetValide(int s, Graphe g){//teste sommet S dans graphe G valide
  return ((s >= 0) && (s < g->nbS));
}

void ajouterArc(int sA, int sB,double dist, Graphe g){
  assert(sommetValide(sA,g));
  Arc a = initArc(sA,sB,dist);
  g->adjs[sA].arcs[g->adjs[sA].nbAdj++] = a;

  assert(sommetValide(sB,g));
  Arc b = initArc(sB,sA,dist);
  g->adjs[sB].arcs[g->adjs[sB].nbAdj++] = b;
}

bool sommetsAdjacent(int sA, int sB, Graphe g){
  int i;
  for(i = 0; i < g->adjs[sA].nbAdj; i++)
    if(estAdjacent(sB,g->adjs[sA].arcs[i]))
      return true;

  return false;
}

double sommetsDistance(int sA, int sB, Graphe g){
  int i;
  for(i = 0; i < g->adjs[sA].nbAdj; i++)
    if(getSommetB(g->adjs[sA].arcs[i]) == sB)
      return getDistance(g->adjs[sA].arcs[i]);
  return -1;
}

void afficherGraphe(Graphe g){
  printf("Graphe de %d sommets\n",g->nbS);
   int i,j;
   for(i = 0; i < g->nbS; i++){
     printf("Sommet %d de %d arcs :\n", i, g->adjs[i].nbAdj);
     for(j = 0; j < g->adjs[i].nbAdj; j++)
       afficherArc(g->adjs[i].arcs[j]);
     printf("\n");
   }
}

void deleteGraphe(Graphe g){
  int i,j;
  for(i = 0; i < g->nbS; i++){
    for(j = 0; j < g->adjs[i].nbAdj; j++)
       free(g->adjs[i].arcs[j]);
     free(g->adjs[i].arcs);
  }
  free(g->adjs);
  free(g);
}
