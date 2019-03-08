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
      if(!(strcmp(plat[ligne][colonne], VIDE))) plein = 0;
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
  /*Si aucune pièce ne peut être prise lors de ce tour, renvoit 0
  Sinon, renvoit 1*/
  /*
  A FAIRE
  */
  return possible;
}

int main(int argc, char * argv[]) {
  char * plat[TAILLE][TAILLE];
  srand(time(NULL));
  int choixMenu = -1;
  int choixMenuIA = -1;
  int choixMenuJ = -1;
  int difficulte = 1; /*Par défaut, la difficulte est sur facile*/
  int cont = 1;
  int nbTours = 1;
  while(choixMenu <= 0 || choixMenu > 3){
    //system("clear");
    printf(" 1 - Joueur contre Joueur\n");
    printf(" 2 - Joueur contre IA\n");
    printf(" 3 - Quitter\n");
    printf("A quoi voulez vous jouer ? : ");
    scanf("%i",&choixMenu);
  }
  choixMenu--;
  if(choixMenu == 2){
    printf("\nAu revoir !\n\n");
    return 0;
  }
  if(choixMenu == 0){
    while(choixMenuJ <= 0 || choixMenu > 3){
      //system("clear");
      printf(" 1 - Joueur Local\n");
      printf(" 2 - Joueur Distant\n");
      printf(" 3 - Quitter\n");
      printf("Quel mode de jeu choisissez vous ? : ");
      scanf("%i",&choixMenuJ);
    }
    choixMenuJ--;
    if(choixMenuJ == 2){
      printf("\nAu revoir !\n\n");
      return 0;
    }
  }else{
    while(choixMenuIA <= 0 || choixMenuIA > 3){
      //system("clear");
      printf(" 1 - IA facile\n");
      printf(" 2 - IA intermédiaire\n");
      printf(" 3 - IA difficile\n");
      printf(" 4 - Quitter\n");
      printf("Quel mode de jeu choisissez vous ? : ");
      scanf("%i",&choixMenuIA);
    }
    choixMenuIA--;
    if(choixMenuIA == 3){
      printf("\nAu revoir !\n\n");
      return 0;
    }
  }
  if(choixMenuIA != -1){
    switch(choixMenuIA){
      case 0 : difficulte = 1 /*MODE FACILE -> coups au hasard uniquement*/;break;
      case 1 : difficulte = 3 /*MODE FACILE -> 1 coup au hasard tout les trois tours*/;break;
      case 2 : difficulte = 10 /*MODE FACILE -> 1 coup au hasard tout les dix tours*/;break;
      default: printf("Une erreur est survenue...");
    }
  }
  void (*tabFoncJ[2])(char * (*)[],char *,int) = {saisieCoupJcJL,saisieCoupJcJD};
  void (*fonc)(char * (*)[],char *,int) = tabFoncJ[0]; // par défaut on est en mode joueur local
  if(choixMenu == 0){
    void (*fonc)(char * (*)[],char *,int) = tabFoncJ[choixMenuJ];
  }
  while(cont){
    //system("clear");
    initPlat(plat);
    //initTestVide(plat);
    //initTestRand(plat);
    //initTestPlein(plat);
    //initTestPasDeBlanc(plat);
    //initTestPasDeNoir(plat);
    printf("Noir : %s / Blanc : %s",NOIR,BLANC);
    char * tour = NOIR;
    //system("clear");
    while(!estFinie(plat)){
      afficherPlateau(plat);
      if(coupPossible(plat,tour)){
        if(choixMenu == 0){
          fonc(plat,tour,nbTours);
        }else{
          saisieCoupJcIA(plat,tour,nbTours,difficulte);
        }
      }
      tour = (tour == NOIR ? BLANC : NOIR);
      nbTours++;
    }
    afficherPlateau(plat);
    afficheScore(plat);
    printf("continuer (0/1) ? : ");
    scanf("%d",&cont);
  }
  //system("clear");
  return 0;
}
