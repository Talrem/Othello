#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./Aff/aff.h"
#include "./Init/init.h"
#include "./Tour/tour.h"
#include "./definitions.h"

int estFinie(char * plat[TAILLE][TAILLE]){
  int done = 0;
  int plein = 1;
  int noirPresent = 0;
  int blancPresent = 0;
  int ligne,colonne;
  for(ligne = 0; ligne < TAILLE; ligne++){
    for(colonne = 0; colonne < TAILLE; colonne++){
      //strcmp renvoit 0 en cas d'égalité des deux termes. Donc on cherche à savoir si
      //Il y a encore au moins une case vide
      if(!(strcmp(plat[ligne][colonne], " "))) plein = 0;
      //Il y a encore au moins une case noire
      if(!(strcmp(plat[ligne][colonne], NOIR))) noirPresent = 1;
      //Il y a encore au moins une case blanche
      if(!(strcmp(plat[ligne][colonne], BLANC))) blancPresent = 1;
    }
  }
  if(plein || !noirPresent || !blancPresent) done = 1;
  return done;
}

int coupPossible(char * plat[TAILLE][TAILLE],char * tour){
  int possible = 1;
  /*
  A FAIRE
  */
  return possible;
}

int main(int argc, char * argv[]) {
  char * plat[TAILLE][TAILLE];
  srand(time(NULL));
  int choixMenu = 0;
  int cont = 1;
  while(!choixMenu){
    system("clear");
    printf(" 1 - Joueur contre Joueur local\n");
    printf(" 2 - Joueur contre Joueur distant\n");
    printf(" 3 - Joueur contre IA facile\n");
    printf(" 4 - Joueur contre IA intermédiaire\n");
    printf(" 5 - Joueur contre IA difficile\n");
    printf(" 6 - Quitter\n");
    printf("A quoi voulez vous jouer ? : ");
    scanf("%i",&choixMenu);
  }
  choixMenu--;
  if(choixMenu == 5){
    printf("\nAu revoir !\n\n");
    return 0;
  }
  void (*tabFonc[5])(char * (*)[],char *) = {saisieCoupJcJL,saisieCoupJcJD,saisieCoupJcIF,saisieCoupJcII,saisieCoupJcID};
  void (*fonc)(char * (*)[],char *) = tabFonc[choixMenu];
  while(cont){
    system("clear");
    initPlat(plat);
    //initTestVide(plat);
    //initTestRand(plat);
    //initTestPlein(plat);
    //initTestPasDeBlanc(plat);
    //initTestPasDeNoir(plat);
    printf("Noir : %s / Blanc : %s",NOIR,BLANC);
    char * tour = NOIR;
    while(!estFinie(plat)){
      system("clear");
      afficherPlateau(plat);
      if(coupPossible(plat,tour)) fonc(plat,tour);
      tour = (tour == NOIR ? BLANC : NOIR);
    }
    afficherPlateau(plat);
    afficheScore(plat);
    printf("continuer (0/1) ? : ");
    scanf("%d",&cont);
  }
  system("clear");
  return 0;
}
