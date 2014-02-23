#include "matrice.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
  Matrice m = initMatrice(2);
  setCell(0,0,m,6);
  showMatrice(m);
  return EXIT_SUCCESS;
}
