#include <stdio.h>
#include <stdlib.h>
#define TAILLE 8
#define NOIR "●"
#define BLANC "○"

void initPlateau(char * plat[TAILLE][TAILLE]){
   int i, j;
   for(i = 0; i < TAILLE; i++){
      for(j = 0; j < TAILLE; j++){
         plat[i][j] = BLANC;
      }
   }
}

void afficherPlateau(char * plat[TAILLE][TAILLE]) {
   int i, j;
   char lettre = 'A';
   printf(" |");
   for(j = 0; j < TAILLE; j++){
      printf("%c ", lettre);
      lettre++;
   }
   printf("\n_|");
   for(j = 0; j < TAILLE; j++){
      printf("__");
   }
   printf("\n");
   for(i = 0; i < TAILLE; i++){
      printf("%d|", i + 1);
      for(j = 0; j < TAILLE; j++){
         printf("%s ", plat[i][j]);
      }
      printf("\n");
   }
}
