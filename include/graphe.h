#ifndef __GRAPHE_H__
#define __GRAPHE_H__

#include <stdbool.h>

struct arc;
struct graphe;
typedef struct arc * Arc;
typedef struct graphe * Graphe;

Arc initArc(int,int,double);
double getDistance(Arc);
bool estAdjacent(int, Arc);
int getSommetA(Arc);
int getSommetB(Arc);
void afficherArc(Arc);
void deleteArc(Arc);

Graphe initGraphe(int);//Graphe de N sommets
Graphe chargerGraphe(char * path);//Graphe a partir d'un fichier tsp

int getNombreSommets(Graphe);//Nombre de sommets de graphe
Arc getArc(int,int,Graphe);
void ajouterArc(int,int,double,Graphe);//ajoute un arc entre deux sommets
void supprimerArc(int,int,Graphe);//supprime les arc (deux sens) entre ville 1 et 2
bool sommetsAdjacent(int,int,Graphe);//vrai si les deux villes possèdent un arc en commun
double sommetsDistance(int,int,Graphe);//distance entre deux sommets adjacents

void afficherGraphe(Graphe);//debug

void deleteGraphe(Graphe);

Arc * getArcs(int*,Graphe);

#endif
