#include "../Aff/aff.h"

void afficherPlateau(char * plat[TAILLE][TAILLE]) {
    int i, j;
    char a = 'A';
    printf("\n");
    for(i = 1;i<=TAILLE+2;i++){
      printf("+---");
    }
    /* Affichage des absices */
    printf ("+\n|   |");
    for (i=1; i<=TAILLE; i++) {
        printf (" %d |", i);
    }
    printf("   |");
    /* Affichage de la grille */
    printf ("\n+");
    for (i=0; i<TAILLE+2; i++)
        printf ("---+");
    printf ("\n");
    for (i=0; i<TAILLE; i++) {
        printf ("| %c ", a);
        for (j=0; j<TAILLE; j++)
                printf ("| %s ", plat[i][j]);
        printf ("| %c |\n+",a++);
        for (j=0; j<=TAILLE+1; j++)
            printf ("---+");
        printf ("\n");
    }
    printf ("|   |");
    for (i=1; i<=TAILLE; i++) {
        printf (" %d |", i);
    }
    printf("   |\n");
    for(i = 1;i<=TAILLE+2;i++){
      printf("+---");
    }
    printf("+\n\n");
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
   printf("\nIl y a %d a %d",scoreB,scoreN);
   scoreB==scoreN?printf(" Egalite.\n"):scoreB>scoreN?printf(", avec un avantage de %d pour les Blancs (%s)\n",abs(scoreB - scoreN), BLANC):printf(", avec un avantage de %d pour les Noirs (%s)\n",abs(scoreB - scoreN),NOIR);
}
