#include "./var.h"

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
    printf("Que choisissez vous ? : ");
    scanf("%i",&choixMenuJD);
    getchar();
  }
  if(choixMenuJD == 3){
    printf("\nAu revoir !\n\n");
    return 0;
  }
  /*
  C'est là qu'il faut mettre le code pour le reseau
  */
  return choixMenuJD;
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
