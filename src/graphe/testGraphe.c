#include "arc.h"

int main(){
  Arc a = initArc(0,0,5.2f);
  Arc b = initArc(1,0,3.1f);
  if(estAdjacent(0,a))toString(a);
  if(estAdjacent(2,b))toString(b);
  deleteArc(a);
  deleteArc(b);
  return 0;
}
