#include <stdio.h>
#include <stdlib.h>
#include "../Aff/aff.h"

void initPlateau(char * plat[TAILLE][TAILLE]){
   for(int i = 0; i < TAILLE;i++){
      for(int j = 0; j < TAILLE;j++){
         plat[i][j] = " ";
      }
   }
}

void initTestRandPlat(char * plat[TAILLE][TAILLE]){
   for(int i = 0; i < TAILLE;i++){
      for(int j = 0; j < TAILLE;j++){
         switch(rand()%3){
            case 0: plat[i][j] = NOIR; break;
            case 1: plat[i][j] = BLANC; break;
            default:break;
         }
      }
   }
}
