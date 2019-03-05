#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../definitions.h"

/*
Cette fonction renvoit si des pions vont être pris.
Elle parcourt le terrain dans chaque direction en partant du point et met les couleurs qu'elle rencontre
-1 pour les " ", 0 pour la couleur adverse et 1 pour la couleur actuelle, dans un tableau
Puis après chaque direction, elle regarde dans le tableau si on a une suite de 0 puis un 1 et si c'est le cas
elle retourne 1 car ça veut dire qu'un pion peut être pris. Sinon elle répète l'opération avec les autres directions
et renvoit 0 sinon*/
int prendPion(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur){
  int aPris = 0;
  int aPoint = 0;
  int aAutreCouleur = 0;
  int points[TAILLE - 1]={-1,-1,-1,-1,-1,-1,-1};
  int i;
  int j;
  /*vers le haut*/
  if(ligne != 0)
    for(i = ligne - 1; i > 0;i--){
      j = colonne;
      if(!strcmp(plat[i][j]," "){
        points[i] = -1;
      }else if(strcmp(plat[i][j],couleur){
        points[i] = 0;
      }
      printf("\nligne : %d\ncolonne :%d\ncase : '%s'",i,j,couleur);
    }
  /*vers le bas*/
  if(ligne + 1 != TAILLE)
    for(i = ligne + 1; i < TAILLE;i++){
      j = colonne;
      if(!strcmp(plat[i][j]," "){
        points[i] = -1;
      }else if(strcmp(plat[i][j],couleur){
        points[i] = 0;
      }
      printf("\nligne : %d\ncolonne :%d\ncase : '%s'",i,j,couleur);
    }
  /*vers la gauche*/
  if(colonne != 0)
    for(j = colonne ; j > 0 ; j--){
      i = ligne;
      if(!strcmp(plat[i][j]," "){
        points[i] = -1;
      }else if(strcmp(plat[i][j],couleur){
        points[i] = 0;
      }
      printf("\nligne : %d\ncolonne :%d\ncase : '%s'",i,j,couleur);
    }
  /*vers la droite*/
  if(colonne + 1 != TAILLE)
  for(j = colonne ; j < TAILLE;j++){
    i = ligne;
    if(!strcmp(plat[i][j]," "){
      points[i] = -1;
    }else if(strcmp(plat[i][j],couleur){
      points[i] = 0;
    }
    printf("\nligne : %d\ncolonne :%d\ncase : '%s'",i,j,couleur);
  }
  /*diagonale HG*/
  /*for(){

  }*/
  /*diagonale HD*/
  /*for(){

  }*/
  /*diagonale BD*/
  /*for(){

  }*/
  /*diagonale BG*/
  /*for(){

  }*/
  return aPris;
}

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
  if(!prendPion(plat,ligne,colonne,couleur)){
    printf("\nLe coup que vous avez voulu jouer ne prend pas de pion adverse...\n");
    return 0;
  }
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
