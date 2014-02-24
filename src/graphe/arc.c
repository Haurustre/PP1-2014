#include "arc.h"
#include <stdlib.h>
#include <stdio.h>

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

void toString(Arc a){
  printf("Arc : Sommet A:%d  Sommet B:%d\n",a->sommetA,a->sommetB);
  printf("Distance:%f\n",a->distance);
}

void deleteArc(Arc a){
  free(a);
}
