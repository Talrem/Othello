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
  char * plat[TAILLE][TAILLE];
  srand(time(NULL));
  int choixMenu = 0;
  while(!choixMenu){
    system("clear");
    printf(" 1 - Joueur contre Joueur local\n");
    printf(" 2 - Joueur contre Joueur distant\n");
    printf(" 3 - Joueur contre IA facile\n");
    printf(" 4 - Joueur contre IA intermédiaire\n");
    printf(" 5 - Joueur contre IA difficile\n");
    printf(" 6 - Quitter\n");
    printf("A quoi voulez vous jouer ? : ");
    scanf("%d",&choixMenu);
    getchar();
  }
  choixMenu--;
  if(choixMenu == 5){
    printf("\nAu revoir !\n\n");
    return 0;
  }
  void (*tabFonc[5])(char * (*)[],char *) = {saisieCoupJcJL,saisieCoupJcJD,saisieCoupJcIF,saisieCoupJcII,saisieCoupJcID};
  void (*fonc)(char * (*)[],char *) = tabFonc[choixMenu];
  initPlateau(plat);
  //initTestRandPlat(plat);
  char * tour = NOIR;
  while(!estFinie(plat)){
    afficherPlateau(plat);
    if(coupPossible(plat,tour)) fonc(plat,tour);
    tour = (tour == NOIR ? BLANC : NOIR);
  }
  afficherPlateau(plat);
  afficheScore(plat);
  return 0;
}
