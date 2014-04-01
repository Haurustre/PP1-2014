#include <graphe.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct arc{
  int sommetA;
  int sommetB;
  double distance;
};

struct Adj{
  int nbAdj;
  Arc * arcs;
};

struct graphe{
  int nbS;
  struct Adj *adjs;  
};

Arc initArc(int a, int b, double dist){
  Arc arc = malloc(sizeof(struct arc));
  arc->sommetA = a;
  arc->sommetB = b;
  arc->distance = dist;
  return arc;
}

double getDistance(Arc a){
  return a->distance;
}

bool estAdjacent(int s, Arc a){
  return( (s == a->sommetA) || (s == a->sommetB) );
}

int getSommetA(Arc a){
  return a->sommetA;
}

int getSommetB(Arc a){
  return a->sommetB;
}

void afficherArc(Arc a){
  printf("%d <--- %f ---> %d\n",a->sommetA,a->distance,a->sommetB);
}

void deleteArc(Arc a){
  free(a);
}

//*************Graphe*****************

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

Graphe chargerGraphe(char * path){
  Graphe g;
  char var[1000];
  int * nbSommetGraphe = malloc(sizeof(int));
  float * valArcGraphe = malloc(sizeof(float));

  printf("Ouverture du fichier %s\n",path);
  FILE * tsp = fopen(path,"r");

  if(tsp == NULL){
    printf(" erreur %d\n",errno);
    if(errno == ENOENT)
      printf("Le fichier n'existe pas !\n");
    else
      printf("Erreur inconnue\n");
  }
  else{
    printf("Creation du Graphe... ");
    fscanf(tsp,"%s",var);
    while(strcmp(var, "DIMENSION:") != 0 && !feof(tsp)){
      fscanf(tsp,"%s",var);
    }
    fscanf(tsp,"%d",nbSommetGraphe);
    g = initGraphe(*nbSommetGraphe);
    
    while(strcmp(var, "EDGE_WEIGHT_SECTION") != 0 && !feof(tsp)){
      fscanf(tsp,"%s",var);
    }

    if( ! feof(tsp)){
      int i,j;
      for(i=0; i< (*nbSommetGraphe); i++){
	for(j=0; j< (*nbSommetGraphe); j++){
	  fscanf(tsp,"%f",valArcGraphe);
	  if(j!=i){
	    Arc a = initArc(i,j,*valArcGraphe);
	    g->adjs[i].arcs[g->adjs[i].nbAdj++] = a;
	  }
	}
      }
    }
    else
      printf("Erreur lors de la lecture du fichier, DIMENSION doit etre specifie avant EDGE_WEIGHT_SECTION\n");
    fclose(tsp);
    printf(" fait\n");
  }
  free(valArcGraphe);
  free(nbSommetGraphe);
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

void supprimerArc(int sA, int sB, Graphe g){
  assert(sommetValide(sA,g));
  assert(sommetValide(sB,g));
  g->adjs[sA].nbAdj = 0;
  g->adjs[sB].nbAdj = 0;
}

bool sommetsAdjacent(int sA, int sB, Graphe g){
  int i;
  for(i = 0; i < g->adjs[sA].nbAdj; i++)
    if(estAdjacent(sB,g->adjs[sA].arcs[i]))
      return true;

  return false;
}

Arc getArc(int sA, int sB, Graphe g){
  int i;
  for(i = 0; i < g->adjs[sA].nbAdj; i++)
    if(estAdjacent(sB,g->adjs[sA].arcs[i]))
      return g->adjs[sA].arcs[i];
  return NULL;
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
     printf("\n");
     for(j = 0; j < g->adjs[i].nbAdj; j++)
       afficherArc(g->adjs[i].arcs[j]);
   }
}

void deleteGraphe(Graphe g){
  int i,j;
  for(i = 0; i < g->nbS; i++){
    for(j = 0; j < g->adjs[i].nbAdj; j++)
       deleteArc(g->adjs[i].arcs[j]);
     free(g->adjs[i].arcs);
  }
  free(g->adjs);
  free(g);
}

Arc * getArcs(int * nbArc,Graphe g){
  int i,j;
  *nbArc = 0;
  Arc * arcs = malloc(sizeof(struct arc)*g->nbS*g->nbS);
  for(i=0;i < g->nbS; i++){
    for(j=0; j < g->adjs[i].nbAdj; j++){
      arcs[(*nbArc)++] = g->adjs[i].arcs[j];
    }
  }

  return arcs;
}
