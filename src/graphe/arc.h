#ifndef __ARC_H__
#define __ARC_H__

#include <stdbool.h>

struct arc{
  int sommetA;
  int sommetB;
  double distance;
};

typedef struct arc * Arc;

Arc initArc(int,int,double);

double getDistance(Arc);
bool estAdjacent(int,Arc);
int getSommetA(Arc);
int getSommetB(Arc);

void afficherArc(Arc);

void deleteArc(Arc);

#endif
