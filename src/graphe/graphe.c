/**
 * \file graphe.c
 * \brief Source de la bibliotheque graphe
 * \author Ghislain Hudry
 * \version 0.1
 * \date 22 Janvier 2014
 *
 * Structure du Graphe et fonction utiles à son fonctionnement
 *
 */
#include <graphe.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

char arc[256]="";

/**
 * \struct arc
 * \brief Objet du Graphe contenant les arêtes
 *
 *  arc est en fait une arrête du graphe contenant deux sommets et
 *  la distance qui les séparent
 */
struct arc{
  int sommetA;
  int sommetB;
  double distance;
};

/**
 * \struct Adj
 * \brief Objet gestion arc du graphe
 *
 *  Adj permet de stocker la liste des arcs accessibles par chacuns
 *  des sommets du graphe
 */
struct Adj{
  int nbAdj;
  Arc * arcs;
};

/**
 * \struct graphe
 * \brief Objet Graphe
 *
 *  Structure contenant l ensemble du Graphe, la liste des arcs de chaque sommet
 * ainsi que le nombre de sommets.
 */
struct graphe{
  int nbS;
  struct Adj *adjs;  
};

/**
 * \fn Arc initArc(int a, int b, double dist)
 * \brief Fonction de création d'une nouvelle instance d'un objet Arc.
 *
 * \param a Premier Sommet de l'arc
 * \param b Deuxieme Sommet de l'arc
 * \param dist La distance séparant les deux sommets
 * \return Instance nouvellement allouée d'un objet de type Arc.
 */
Arc initArc(int a, int b, double dist){
  Arc arc = malloc(sizeof(struct arc));
  arc->sommetA = a;
  arc->sommetB = b;
  arc->distance = dist;
  return arc;
}

/**
 * \fn double getDistance(Arc a)
 * \brief Fonction renvoie la distance contenue dans l'Arc a.
 *
 * \param a Arc dont on veux obtenir la distance
 * \return Nombre Réel de type double contenant la distance de l'Arc.
 */
double getDistance(Arc a){
  return a->distance;
}

/**
 * \fn bool estAdjacent(int s, Arc a)
 * \brief Fonction teste si adjacent
 *
 * \param s Sommet à tester
 * \param a Arc à tester
 * \return Vrai si le sommet s est un des sommets de l'Arc a dans le graphe.
 */
bool estAdjacent(int s, Arc a){
  return( (s == a->sommetA) || (s == a->sommetB) );
}

/**
 * \fn int getSommetA(Arc a)
 * \brief Fonction renvoie le premier Sommet.
 *
 * \param a Arc à tester
 * \return Valeur du Premier sommet de la structure Arc.
 */
int getSommetA(Arc a){
  return a->sommetA;
}

/**
 * \fn int getSommetB(Arc a)
 * \brief Fonction renvoie le second Sommet.
 *
 * \param a Arc à tester
 * \return Valeur du second sommet de la structure Arc.
 */
int getSommetB(Arc a){
  return a->sommetB;
}

/**
 * \fn char * afficherArc(Arc a)
 * \brief Fonction affichage Arc.
 *
 * \param a Arc à afficher
 * \return Chaîne de charactère corespondant à l'affichage d'un arc
 * en Shell.
 */
char * afficherArc(Arc a){
  arc[0] ='\0';
  sprintf(arc,"%s%d->%d:%f; ",arc,a->sommetA,a->sommetB,a->distance);

  return arc;
}

/**
 * \fn void deleteArc(Arc a)
 * \brief Libérer Arc
 *
 * \param a Arc à désallouer.
 * \return void
 */
void deleteArc(Arc a){
  free(a);
}

//*************Graphe*****************

/**
 * \fn Graphe initGraphe(int nombreSommet)
 * \brief Initialisation du Graphe
 *
 * \param nombreSommet Nombre de sommets dans le graphe
 * \return Graphe de 'nombreSommet' sommets nouvellement alloué
 */
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

/**
 * \fn Graphe chargerGraphe(char * path)
 * \brief Parser, chargement du graphe via un fichier
 *
 * \param path Chemin jusqu'au fichier .tsp contenant le problème à transformer sous forme de graphe
 * \return Graphe nouvellement alloué
 */
Graphe chargerGraphe(char * path){
  Graphe g;
  char var[1000];
  int * nbSommetGraphe = malloc(sizeof(int));
  float * valArcGraphe = malloc(sizeof(float));

  //printf("Ouverture du fichier %s\n",path);
  FILE * tsp = fopen(path,"r");

  if(tsp == NULL){
    printf(" erreur %d\n",errno);
    if(errno == ENOENT)
      printf("Le fichier n'existe pas !\n");
    else
      printf("Erreur inconnue\n");
  }
  else{
    //printf("Creation du Graphe... ");
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
    //printf(" fait\n");
  }
  free(valArcGraphe);
  free(nbSommetGraphe);
  return g;
}

int getNombreSommets(Graphe g){
  return g->nbS;
}

/**
 * \fn bool sommetValide(int s, Graphe g)
 * \brief Teste de la validité d'un sommet.
 *
 * \param s Sommet à tester
 * \param g Graphe dans lequel doit etre present le sommet s
 * \return TRUE si le sommet est bien dans le graphe.
 */
bool sommetValide(int s, Graphe g){//teste sommet S dans graphe G valide
  return ((s >= 0) && (s < g->nbS));
}

/**
 * \fn void ajouterArc(int sA, int sB,double dist, Graphe g)
 * \brief Ajoute un Arc au Graphe.
 *
 * \param sA Premier sommet de l'arc
 * \param sB Second sommet de l'arc
 * \param dist Longueur de l'arc
 * \param g Graphe dans lequel est ajouté l'arc nouvellement alloué
 * \return void
 */
void ajouterArc(int sA, int sB,double dist, Graphe g){
  assert(sommetValide(sA,g));
  Arc a = initArc(sA,sB,dist);
  g->adjs[sA].arcs[g->adjs[sA].nbAdj++] = a;

  assert(sommetValide(sB,g));
  Arc b = initArc(sB,sA,dist);
  g->adjs[sB].arcs[g->adjs[sB].nbAdj++] = b;
}

/**
 * \fn void supprimerArc(int sA, int sB, Graphe g)
 * \brief Enleve un Arc du graphe
 *
 * \param sA Premier sommet de l'arc
 * \param sB Second sommet de l'arc
 * \param g Graphe
 * \return void
 */
void supprimerArc(int sA, int sB, Graphe g){
  assert(sommetValide(sA,g));
  assert(sommetValide(sB,g));
  g->adjs[sA].nbAdj = 0;
  g->adjs[sB].nbAdj = 0;
}

/**
 * \fn bool sommetsAdjacent(int sA, int sB, Graphe g)
 * \brief Teste d'adjacence entre deux sommets
 *
 * \param sA Premier sommet
 * \param sB Second sommet
 * \param g Graphe
 * \return void
 */
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

/**
 * \fn double sommetsDistance(int sA, int sB, Graphe g)
 * \brief Distance entre deux sommets du Graphe
 *
 * \param sA Premier sommet
 * \param sB Second sommet
 * \param g Graphe
 * \return Distance (direct) entre deux sommets, si ils ne sont pas adjacent -1
 */
double sommetsDistance(int sA, int sB, Graphe g){
  int i;
  for(i = 0; i < g->adjs[sA].nbAdj; i++)
    if(getSommetB(g->adjs[sA].arcs[i]) == sB)
      return getDistance(g->adjs[sA].arcs[i]);
  return -1;
}

/**
 * \fn void afficherGraphe(Graphe g, char * ret)
 * \brief Affiche le Graphe
 *
 * \param g Graphe
 * \param ret Chaîne de charactère contenant l'affichage
 * \return void
 */
void afficherGraphe(Graphe g, char * ret){
  ret[0] = '\0';
  sprintf(ret,"Graphe de %d sommets",g->nbS);
   int i,j;
   for(i = 0; i < g->nbS; i++){
     strcat(ret, "\n");
     for(j = 0; j < g->adjs[i].nbAdj; j++){
       strcat(ret,afficherArc(g->adjs[i].arcs[j]));
     }
   }
}
void afficherGrapheTerminal(Graphe g){
  printf("Graphe de %d sommets\n",g->nbS);
   int i,j;
   for(i = 0; i < g->nbS; i++){
     printf("\n");
     for(j = 0; j < g->adjs[i].nbAdj; j++)
       printf("%s\n",afficherArc(g->adjs[i].arcs[j]));
   }
   printf("\n");
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

/**
 * \fn Arc * getArcs(int * nbArc,Graphe g)
 * \brief Liste de tous les arcs du Graphe
 *
 * \param nbArc le nombre d'arc du graphe (par référence afin de récupérer en retour le nombre)
 * \param g Graphe
 * \return Tableau d'arcs
 */
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
