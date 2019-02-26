#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./aff.h"
#include "./init.h"

int main() {
   system("clear");
   char * plat[TAILLE][TAILLE];
   srand(time(NULL));
   initPlateau(plat);
   initTestRandPlat(plat);
   afficherPlateau(plat);
   afficheScore(plat);
   return 0;
}
