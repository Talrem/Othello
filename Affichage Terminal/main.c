#include <stdio.h>
#include <stdlib.h>
#include "testaff.h"

int main() {
   char * plat[TAILLE][TAILLE];
   initPlateau(plat);
   afficherPlateau(plat);
   return 0;
}
