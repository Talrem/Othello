#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Aff/aff.h"
#include "./Init/init.h"
#include "./Tour/tour.h"

int estFinie(char * plat[TAILLE][TAILLE]){
  int done = 0;
  return done;
}

int coupPossible(char * plat[TAILLE][TAILLE],char * tour){
  int possible = 1;
  return possible;
}

int main(int argc, char * argv[]) {
  system("clear");
  char * plat[TAILLE][TAILLE];
  srand(time(NULL));
  initPlateau(plat);
  //initTestRandPlat(plat);
  char * tour = NOIR;
  while(!estFinie(plat)){
    afficherPlateau(plat);
    if(coupPossible(plat,tour)) saisieCoup(plat,tour);
    tour = (tour == NOIR ? BLANC : NOIR);
  }
  afficherPlateau(plat);
  afficheScore(plat);
  return 0;
}
