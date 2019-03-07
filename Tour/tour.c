#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../definitions.h"

/*
Cette fonction regarde dans le tableau si on a une suite de 0 puis un 1 et si c'est le cas
elle retourne 1 car ça veut dire qu'un pion peut être pris. Si un -1 est trouvé, c'est qu'il y a un espace
donc inutile de continuer.
*/
int checkTableau(int tab[]){
  int i;
  int suite = 0;
  for(i = 0 ; i < TAILLE ; i++){
    if(tab[i] == -1) return 0;
    if(tab[i] == 0){
      suite = 1;
    }else if(tab[i] == 1 && suite){
      return 1;
    }
  }
  return 0;
}

void initTableau(int tab[]){
  for(int i = 0 ; i < TAILLE - 1 ; i ++){
    tab[i] = -1;
  }
}

/*
Cette fonction renvoit si des pions vont être pris.
Elle parcourt le terrain dans chaque direction en partant du point et met les couleurs qu'elle rencontre
-1 pour les " ", 0 pour la couleur adverse et 1 pour la couleur actuelle, dans un tableau
Puis après chaque direction, le tableau est vérifié et si un pion est pris, on renvoit 1 sinon elle répète l'opération avec les autres directions
et renvoit si aucun pion n'a été pris
*/

int prendPion(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur){
  int aPris = 0;
  int points[TAILLE - 1];
  initTableau(points);
  int i;
  int j;
  int compteur = 0;
  /*vers le haut*/
  if(ligne != 0){
    j = colonne;
    for(i = ligne - 1 ; i > 0 ; i--){
      if(!strcmp(plat[i][j]," ")){
        points[compteur++] = -1;
      }else if(strcmp(plat[i][j],couleur)){
        points[compteur++] = 0;
      }else{
        points[compteur++] = 1;
      }
    }
    aPris = checkTableau(points);
  }
  compteur = 0;
  initTableau(points);
  /*vers le bas*/
  if(ligne + 1 != TAILLE && aPris == 0){
    j = colonne;
    for(i = ligne + 1 ; i < TAILLE ; i++){
      if(!strcmp(plat[i][j]," ")){
        points[compteur++] = -1;
      }else if(strcmp(plat[i][j],couleur)){
        points[compteur++] = 0;
      }else{
        points[compteur++] = 1;
      }
    }
    aPris = checkTableau(points);
  }
  compteur = 0;
  initTableau(points);
  /*vers la gauche*/
  if(colonne != 0 && aPris == 0){
    i = ligne;
    for(j = colonne - 1; j >= 0 ; j--){
      if(!strcmp(plat[i][j]," ")){
        points[compteur++] = -1;
      }else if(strcmp(plat[i][j],couleur)){
        points[compteur++] = 0;
      }else{
        points[compteur++] = 1;
      }
    }
    aPris = checkTableau(points);
  }
  compteur = 0;
  initTableau(points);
  /*vers la droite*/
  if(colonne + 1 != TAILLE && aPris == 0){
    i = ligne;
    for(j = colonne + 1; j < TAILLE ; j++){
      if(!strcmp(plat[i][j]," ")){
        points[compteur++] = -1;
      }else if(strcmp(plat[i][j],couleur)){
        points[compteur++] = 0;
      }else{
        points[compteur++] = 1;
      }
    }
    aPris = checkTableau(points);
  }
  compteur = 0;
  initTableau(points);
  /*diagonale HG*/
  if(colonne != 0 && ligne != 0 && aPris == 0){
    for(i = ligne - 1 ; i >= 0 ; i--){
      j = colonne - 1 - i;
      if(j >= 0){
        if(!strcmp(plat[i][j]," ")){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
    }
    aPris = checkTableau(points);
  }
  compteur = 0;
  initTableau(points);
  /*diagonale HD*/
  if(ligne != 0 && colonne + 1 != TAILLE && aPris == 0){
    for(i = ligne - 1 ; i >= 0 ; i--){
      j = colonne + 1 + i;
      if(j >= 0){
        if(!strcmp(plat[i][j]," ")){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
    }
    aPris = checkTableau(points);
  }
  compteur = 0;
  initTableau(points);
  /*diagonale BD*/
  if(ligne + 1 != TAILLE && colonne + 1 != TAILLE && aPris == 0){
    for(i = ligne + 1 ; i < TAILLE ; i++){
      j = ligne + 1 + i;
      if(j <= TAILLE - 1){
        if(!strcmp(plat[i][j]," ")){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
    }
    aPris = checkTableau(points);
  }
  compteur = 0;
  initTableau(points);
  /*diagonale BG*/
  if(ligne != TAILLE && colonne != 0 && aPris == 0){
    for(i = ligne + 1 ; i < TAILLE ; i++){
      j = ligne + 1 + i;
      if(j <= TAILLE - 1){
        if(!strcmp(plat[i][j]," ")){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
    }
    aPris = checkTableau(points);
  }
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
