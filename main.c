#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Aff/aff.h"
#include "./Init/init.h"

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
