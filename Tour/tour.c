#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Aff/aff.h"

/*
Cette fonction vérifie la validité du coup
Applique les changements au plateau
Renvoit si oui ou non il y a eu une modification
*/
int estValide(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur){
  int coupValide = 0;
  //coup dans le plateau.
  if(ligne >= TAILLE || ligne < 0 || colonne >= TAILLE || colonne < 0){
    printf("\nLe coup que vous avez voulu jouer est en dehors du plateau...\n");
    return 0;
  }
  //coup dans une case vide.
  if((strcmp(plat[ligne][colonne], " "))){
    printf("\nLe coup que vous avez voulu jouer n'est pas une case vide...\n");
    return 0;
  }
  //coup prend un pion adverse.
  /*
  A FAIRE
  */
  plat[ligne][colonne] = couleur;
  return 1;
}

//Joueur contre IA difficile
void saisieCoupJcID(char * plat[TAILLE][TAILLE], char * couleur){
  printf("Work In Progress\nAu Revoir\n");
  exit(EXIT_SUCCESS);
}

//Joueur contre IA intermédiaire
void saisieCoupJcII(char * plat[TAILLE][TAILLE], char * couleur){
  printf("Work In Progress\nAu Revoir\n");
  exit(EXIT_SUCCESS);
}

//Joueur contre IA facile
void saisieCoupJcIF(char * plat[TAILLE][TAILLE], char * couleur){
  printf("Work In Progress\nAu Revoir\n");
  exit(EXIT_SUCCESS);
}

//Joueur contre Joueur distant
void saisieCoupJcJD(char * plat[TAILLE][TAILLE], char * couleur){
  printf("Work In Progress\nAu Revoir\n");
  exit(EXIT_SUCCESS);
}

//Joueur contre Joueur local
void saisieCoupJcJL(char * plat[TAILLE][TAILLE], char * couleur){
  int coupValide = 0;
  int colonne = -1,ligne = -1;
  char saisieLigne = ' ';
  printf("\nJoueur %s\n",couleur);
  while(!coupValide){
    printf("Saisissez votre coup (ligne colonne) : ");
    scanf("%c%d",&saisieLigne,&colonne);
    getchar();
    //Transformation de la lettre en indice de ligne
    if(saisieLigne >= 'A' && saisieLigne <= 'A' + TAILLE){
      ligne = saisieLigne - 'A';
    }else{
      ligne = saisieLigne - 'a';
    }
    colonne--;
    coupValide = estValide(plat,ligne,colonne,couleur);
  }
}
