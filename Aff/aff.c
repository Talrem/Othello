#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 8
#define NOIR "●"
#define BLANC "○"

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

void afficheScore(char * plat[TAILLE][TAILLE]){
   int scoreB = 0, scoreN = 0;
   int i, j;
   for(i = 0; i < TAILLE;i++){
      for(j = 0; j < TAILLE;j++){
         if(!(strcmp(plat[i][j], NOIR))){
            scoreN++;
         }
         if(!(strcmp(plat[i][j], BLANC))){
            scoreB++;
         }
      }
   }
   printf("\nIl y a %d à %d",scoreB,scoreN);
   scoreB==scoreN?printf(" Egalite.\n"):scoreB>scoreN?printf(", avec un avantage de %d pour les Blancs\n",abs(scoreB - scoreN)):printf(", avec un avantage de %d pour les Noirs\n",abs(scoreB - scoreN));
}
