#include "./Aff/aff.h"
#include "./Init/init.h"
#include "./Tour/tour.h"
#include "./Var/var.h"
#include "./Reseau/reseau.h"
#include "./definitions.h"

int main(int argc, char * argv[]){
  char * plat[TAILLE][TAILLE];
  srand(time(NULL));
  int choixMenu = -1,choixMenuIA = -1,choixMenuJ = -1,choixMenuJD = -1;
  /*Par defaut, la difficulte est sur facile*/
  int difficulte = 1;
  /*Si la couleur de l'IA est 1 alors elle jouera les noirs, sinon elle jouera les blancs*/
  char saisieCouleurIA;
  int couleurIA = -1;
  int cont = 1;
  int nbTours = 1;
  /*Pour les prompts*/
  char command, enter;
  int again;
  choixMenu = menu(choixMenu);
  switch (choixMenu) {
    case 1: choixMenuJ = menuJcJ(choixMenuJ);
      switch (choixMenuJ) {
        case 1:break;
        case 2:
          choixMenuJD = menuJD(choixMenuJD);
          return 0;
        default:
          return printf("\nUne erreur est survenue...\n");
      }
      break;
    case 2:
      choixMenuIA = menuIA(choixMenuIA);
      difficulte = difficulteIA(choixMenuIA);
      couleurIA = choixCouleurIA();
      break;
    default:
      return printf("\nUne erreur est survenue...\n");
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
        //nbTours = initPlatFic(plat,fichier,);
        fclose(fichier);
        break;
      case 'n':
        initPlat(plat);
        break;
      default:
        return printf("Une erreur est survenue...");
    }
    system("clear");
    char * tour = NOIR;
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
