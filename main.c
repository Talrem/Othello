#include "./Aff/aff.h"
#include "./Init/init.h"
#include "./Tour/tour.h"
#include "./Reseau/reseau.h"
#include "./definitions.h"

/*
  Fonction qui renvoit si une partie est fini et qui gagne.
  0 -> la partie n'est pas encore finie
  1 -> les blancs
  2 -> les noirs
  3 -> égalité
*/
int estFinie(char * plat[TAILLE][TAILLE]){
  int done = 0;
  int plein = 1;
  int nbNoirs = 0;
  int nbBlancs = 0;
  int ligne,colonne;
  for(ligne = 0; ligne < TAILLE; ligne++){
    for(colonne = 0; colonne < TAILLE; colonne++){
      // strcmp renvoit 0 en cas d'égalité des deux termes. Donc on cherche à savoir si
      // Il y a encore au moins une case vide
      if(!(strcmp(plat[ligne][colonne], VIDE))) plein = 0;
      // Il y a encore au moins une case noire
      if(!(strcmp(plat[ligne][colonne], NOIR))) nbNoirs++;
      // Il y a encore au moins une case blanche
      if(!(strcmp(plat[ligne][colonne], BLANC))) nbBlancs++;
    }
  }
  if(plein || !nbNoirs || !nbBlancs) done = nbNoirs>nbBlancs?1:nbNoirs<nbBlancs?2:3;
  return done;
}

/*
  Fonction qui renvoit si un coup est possible dans une situation donnée et pour un joueur donné
*/
int coupPossible(char * plat[TAILLE][TAILLE] ,char * couleur){
  int possible = 0;
  int i, j;
  for(i = 0; i < TAILLE ; i++){
    for(j = 0; j < TAILLE ; j++){
      if(!estInvalide(plat,i,j,couleur,1)) possible = 1;
    }
  }
  return possible;
}

int main(int argc, char * argv[]){
  char * plat[TAILLE][TAILLE];
  srand(time(NULL));
  int choixMenu = -1;
  int choixMenuIA = -1;
  int choixMenuJ = -1;
  int choixMenuJD = -1;
  /*Par défaut, la difficulte est sur facile*/
  int difficulte = 1;
  /*Si la couleur de l'IA est 1 alors elle jouera les noirs, sinon elle jouera les blancs*/
  int couleurIA = rand()%2;
  int cont = 1;
  int nbTours = 1;
  while(choixMenu <= 0 || choixMenu > 3){
    system("clear");
    printf(" 1 - Joueur contre Joueur\n");
    printf(" 2 - Joueur contre IA\n");
    printf(" 3 - Quitter\n");
    printf("A quoi voulez vous jouer ? : ");
    scanf("%i",&choixMenu);
    getchar();
  }
  if(choixMenu == 3){
    printf("\nAu revoir !\n\n");
    return 0;
  }
  if(choixMenu == 1){
    while(choixMenuJ < 1 || choixMenuJ > 3){
      system("clear");
      printf(" 1 - Joueur Local\n");
      printf(" 2 - Joueur Distant\n");
      printf(" 3 - Quitter\n");
      printf("Quel mode de jeu choisissez vous ? : ");
      scanf("%i",&choixMenuJ);
      getchar();
    }
    if(choixMenuJ == 3){
      printf("\nAu revoir !\n\n");
      return 0;
    }else if(choixMenuJ == 2){
      while(choixMenuJD < 1 || choixMenuJD > 3){
        system("clear");
        printf(" 1 - Héberger une partie\n");
        printf(" 2 - Rejoindre une partie\n");
        printf(" 3 - Quitter\n");
        printf("Que choisissez vous ? : ");
        scanf("%i",&choixMenuJD);
        getchar();
      }
      /*
      C'est là qu'il faut mettre le code pour le réseau
      */
    }
  }else{
    while(choixMenuIA < 1 || choixMenuIA > 5){
      system("clear");
      printf(" 1 - IA facile\n");
      printf(" 2 - IA intermédiaire\n");
      printf(" 3 - IA difficile\n");
      printf(" 4 - IA expert\n");
      printf(" 5 - Quitter\n");
      printf("Quel mode de jeu choisissez vous ? : ");
      scanf("%i",&choixMenuIA);
      getchar();
    }
    if(choixMenuIA == 5){
      printf("\nAu revoir !\n\n");
      return 0;
    }
  }
  if(choixMenuIA != -1){
    switch(choixMenuIA){
      case 1 : difficulte = 1 /*MODE FACILE -> coups au hasard uniquement*/;break;
      case 2 : difficulte = 3 /*MODE INTERMEDIAIRE -> 1 coup au hasard tout les trois tours*/;break;
      case 3 : difficulte = 10 /*MODE DIFFICILE -> 1 coup au hasard tout les dix tours*/;break;
      case 4 : difficulte = 70 /*MODE ULTRA -> pas de coups au hasard*/;break;
      default: printf("Une erreur est survenue...");
    }
  }
  system("clear");
  while(cont){
    initPlat(plat);
    // initTestVide(plat);
    // initTestRand(plat);
    // initTestPlein(plat);
    // initTestPasDeBlanc(plat);
    // initTestPasDeNoir(plat);
    char * tour = NOIR;
    switch(choixMenuJ){
      case 2:
        while(!estFinie(plat)){
          printf("Noir : %s / Blanc : %s",NOIR,BLANC);
          afficherPlateau(plat);
          if(coupPossible(plat,tour)) saisieCoupJcJD(plat,tour,nbTours);
          tour = (tour == NOIR ? BLANC : NOIR);
          nbTours++;
        }
        break;
      default:
        while(!estFinie(plat)){
          printf("Noir : %s / Blanc : %s",NOIR,BLANC);
          afficherPlateau(plat);
          if(coupPossible(plat,tour)){
            if(choixMenu == 1){
              saisieCoupJcJL(plat,tour,nbTours);
            }else{
              saisieCoupJcIA(plat,tour,nbTours,difficulte,couleurIA);
            }
          }
          tour = (tour == NOIR ? BLANC : NOIR);
          nbTours++;
        }
        break;
    }
    afficherPlateau(plat);
    afficheScore(plat);
    printf("continuer (0/1) ? : ");
    scanf("%d",&cont);
    getchar();
    nbTours = 0;
    couleurIA = (couleurIA == 1 ? 2 : 1);
  }
  printf("Au revoir.\n");
  return 0;
}
