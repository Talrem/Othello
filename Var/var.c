#include "./var.h"
#include "../Reseau/reseau.h"
#include "../Tour/tour.h"
#include "../Aff/aff.h"
#include "../Init/init.h"
/*Choix du mode de jeu*/
int menu(int choixMenu){
  while(choixMenu < 1 || choixMenu > 3){
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
  return choixMenu;
}

/*Menu Joueur contre Joueur*/
int menuJcJ(int choixMenuJ){
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
  }
  return choixMenuJ;
}

/*Menu Serveur*/
int menuJD(int choixMenuJD){
  while(choixMenuJD < 1 || choixMenuJD > 3){
    system("clear");
    printf(" 1 - Heberger une partie\n");
    printf(" 2 - Rejoindre une partie\n");
    printf(" 3 - Quitter\n");
    printf("\nINFO: L'hébergeur de la partie joue les pions noir et le joueur adverse les pions blanc\n");
    printf("\nQue choisissez vous ? : ");
    scanf("%i",&choixMenuJD);
    getchar();
  }
  // socket réseau
  SOCKET sock;
  SOCKET ssock;
  SOCKET csock;
  // jeu
  char * plat[TAILLE][TAILLE];
  initPlat(plat);
  int coupDonnee[2];
  int coupLigne;
  int coupColonne;
  char * tour;
  int nbTours = 1;

  if(choixMenuJD == 1){
    tour = NOIR;
    if ((ssock = serveur(sock)) == 0){
      printf("Vérifier que l'adresse IP de l'un de vos interfaces ethernet soit exact\n");
      return 0;
    }
  }

  if(choixMenuJD == 2){
    tour = BLANC;
    if ((csock = client(sock)) == 0){
      printf("Vérifier que vous saissisez bien l'adresse IP du serveur\n");
      printf("Vérifier que votre adresse IP soit sur le même réseau que celui du serveur\n");
      return 0;
    }
  }

  if(choixMenuJD == 3){
    printf("\nAu revoir !\n\n");
    return 0;
  }

  while(!estFinie(plat)){
    afficherPlateau(plat);
    printf("Noir : %s / Blanc : %s\n",NOIR,BLANC);
    printf("Tour: %d\n",nbTours);
    if (choixMenuJD == 1){ // On est herbergeur SERVEUR
        if (nbTours % 2 != 0){ //Si tour impair
          if(coupPossible(plat,tour)){
            saisieCoupJcJD(plat,tour,nbTours,coupDonnee);
            if(send(ssock,&coupDonnee,sizeof(coupDonnee), 0) != SOCKET_ERROR){
              nbTours++;}
          }
        }
        else{ //Si le tour est pair
          int coupRecu[2];
          printf("En attente du joueur adverse...\n");
          if(recv(ssock,&coupRecu,sizeof(coupRecu), 0) != SOCKET_ERROR){
            system("clear");
            coupLigne = coupRecu[0];
            coupColonne = coupRecu[1];
            estInvalide(plat,coupLigne,coupColonne,BLANC,0);
            plat[coupLigne][coupColonne] = BLANC;
            nbTours++;
          }
        }
      }

    /////////////////////////////////////////////////////////////////////////////////////

    if (choixMenuJD == 2){ // On rejoint la partie CLIENT
        if (nbTours % 2 == 0){ //Si tour pair
          if(coupPossible(plat,tour)){
            saisieCoupJcJD(plat,tour,nbTours,coupDonnee);
            if(send(csock,&coupDonnee,sizeof(coupDonnee), 0) != SOCKET_ERROR){
              nbTours++;}
          }
        }
        else{ // Si tour est impair
          int coupRecu[2];
          printf("En attente du joueur adverse...\n");
          if(recv(csock,&coupRecu,sizeof(coupRecu), 0) != SOCKET_ERROR) {
            system("clear");
            coupLigne = coupRecu[0];
            coupColonne = coupRecu[1];
            estInvalide(plat,coupLigne,coupColonne,NOIR,0);
            plat[coupLigne][coupColonne] = NOIR;
            nbTours++;
          }
        }
      }
    }
if (choixMenuJD == 1){
shutdown(ssock,2);
deconnexion(ssock);
}
else{
deconnexion(csock);
}
afficherPlateau(plat);
afficheScore(plat);
printf("Partie terminée\n");
getchar();
return 0;
}

/*Menu Joueur contre IA*/
int menuIA(int choixMenuIA){
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
  return choixMenuIA;
}

/*Noire Blanche ou Aléatoire*/
int choixCouleurIA(){
  int couleurIA;
  /*Choix de la couleur de l'IA. On ne peut choisir que pour la première partie.
  Pour les parties suivante, l'IA change de couleur à chaque fois*/
  char c;
  printf("Quelle est la couleur de l'IA ? n(oire) / b(lanche) / a(leatoire) : ");
  scanf("%c", &c);
  switch(c){
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
  return couleurIA;
}

/*1 - 3 - 10 - 70*/
int difficulteIA(int choixMenuIA){
  int difficulte;
  switch(choixMenuIA){
    case 1 : difficulte = 1 /*MODE FACILE -> coups au hasard uniquement*/;break;
    case 2 : difficulte = 3 /*MODE INTERMEDIAIRE -> 1 coup au hasard tout les 3 tours*/;break;
    case 3 : difficulte = 10 /*MODE DIFFICILE -> 1 coup au hasard tout les 10 tours*/;break;
    case 4 : difficulte = 70 /*MODE ULTRA -> pas de coups au hasard (70 > au nombre de tours max)*/;break;
    default: return printf("Une erreur est survenue...");
  }
  return difficulte;
}
