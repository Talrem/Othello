#include "./Aff/aff.h"
#include "./Init/init.h"
#include "./Tour/tour.h"
/*#include "./Reseau/reseau.h"*/
#include "./definitions.h"

int main(int argc, char * argv[]){
  char * plat[TAILLE][TAILLE];
  srand(time(NULL));
  int choixMenu = -1;
  int choixMenuIA = -1;
  int choixMenuJ = -1;
  int choixMenuJD = -1;
  /*Par defaut, la difficulte est sur facile*/
  int difficulte = 1;
  /*Si la couleur de l'IA est 1 alors elle jouera les noirs, sinon elle jouera les blancs*/
  char saisieCouleurIA;
  int couleurIA = -1;
  int cont = 1;
  int nbTours = 1;
  char command, enter;
  int again;
  /*Choix du mode de jeu*/
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
  /*Menu Joueur contre Joueur*/
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
    }else
    /*Menu Serveur*/
    if(choixMenuJ == 2){
      while(choixMenuJD < 1 || choixMenuJD > 3){
        system("clear");
        printf(" 1 - Heberger une partie\n");
        printf(" 2 - Rejoindre une partie\n");
        printf(" 3 - Quitter\n");
        printf("Que choisissez vous ? : ");
        scanf("%i",&choixMenuJD);
        getchar();
      }
      /*
      C'est là qu'il faut mettre le code pour le reseau
      */
    }
  }else{
  /*Menu Joueur contre IA*/
    while(choixMenuIA < 1 || choixMenuIA > 5){
      system("clear");
      printf(" 1 - IA facile\n");
      printf(" 2 - IA intermediaire\n");
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
      case 2 : difficulte = 3 /*MODE INTERMEDIAIRE -> 1 coup au hasard tout les 3 tours*/;break;
      case 3 : difficulte = 10 /*MODE DIFFICILE -> 1 coup au hasard tout les 10 tours*/;break;
      case 4 : difficulte = 70 /*MODE ULTRA -> pas de coups au hasard (70 > au nombre de tours max)*/;break;
      default: return printf("Une erreur est survenue...");
    }
    /*Choix de la couleur de l'IA. On ne peut choisir que pour la première partie.
    Pour les parties suivante, l'IA change de couleur à chaque fois*/
    if(couleurIA == -1){
      printf("Quelle est la couleur de l'IA ? n(oire) / b(lanche) / a(leatoire) : ");
      scanf("%c", &command);
      switch(command){
        case 'n':
          couleurIA = 1;
          break;
        case 'b':
          couleurIA = 0;
          break;
        default:
          couleurIA = rand()%2;
          break;
      }
      getchar();
    }
  }
  system("clear");
  while (cont) {
    do{
      printf("Souhaitez vous charger une partie ? o(ui) / n(on) : ");
      scanf("%c", &command);
      again = command != 'o' && command != 'n';
    }while (again);
    getchar();
    switch(command){
      case 'o':
        system("clear");
        FILE * fichier;
        char fileName[30];
        printf("Saisissez le nom du fichier pour charger la partie : ");
        scanf("%s",fileName);
        fichier = fopen(strcat(fileName,".txt"),"r");
        nbTours = initPlatFic(plat,fichier);
        fclose(fichier);
        break;
      case 'n':
        initPlat(plat);
        // initTestVide(plat);
        // initTestRand(plat);
        // initTestPlein(plat);
        // initTestPasDeBlanc(plat);
        // initTestPasDeNoir(plat);
        break;
      default:
        printf("Une erreur est survenue...");
        return 0;
    }
    system("clear");
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
    couleurIA = (couleurIA == 1 ? 0 : 1);
  }
  printf("Au revoir.\n");
  return 0;
}
