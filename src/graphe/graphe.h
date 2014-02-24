#ifndef __GRAPHE_H__
#define __GRAPHE_H__

#include "arc.h"
#include <stdbool.h>

struct Adj{
  int nbAdj;
  Arc * arcs;
};

struct graphe{
  int nbS;
  struct Adj *adjs;  
};

typedef struct graphe * Graphe;

Graphe initGraphe(int);//Graphe de N sommets

int getNombreSommets(Graphe);//Nombre de sommets de graphe
void ajouterArc(int,int,double,Graphe);//ajoute un arc entre deux sommets
bool sommetsAdjacent(int,int,Graphe);//vrai si les deux villes possèdent un arc en commun
double sommetsDistance(int,int,Graphe);//distance entre deux sommets adjacents

void afficherGraphe(Graphe);//debug

void deleteGraphe(Graphe);

#endif
