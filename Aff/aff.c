#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Aff/aff.h"

void afficherPlateau(char * plat[TAILLE][TAILLE]) {
    int i, j;
    char a = 'A';
    printf("\n");
    for(i = 1;i<=TAILLE+1;i++){
      printf("o~~~");
    }
    /* Affichage des absices */
    printf ("o\n|   |");
    for (i=1; i<=TAILLE; i++) {
        printf (" %d |", i);
    }
    /* Affichage de la grille */
    printf ("\no");
    for (i=0; i<TAILLE+1; i++)
        printf ("~~~o");
    printf ("\n");
    for (i=0; i<TAILLE; i++) {
        printf ("| %c ", a++);
        for (j=0; j<TAILLE; j++)
                printf ("| %s ", plat[i][j]);
        printf ("|\no");
        for (j=0; j<=TAILLE; j++)
            printf ("~~~o");
        printf ("\n");
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
