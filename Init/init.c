#include <stdio.h>
#include <stdlib.h>
#include "../Aff/aff.h"

void initPlateau(char * plat[TAILLE][TAILLE]){
   for(int i = 0; i < TAILLE;i++){
      for(int j = 0; j < TAILLE;j++){
        if(i == 3 && j == 3 || i == 4 && j == 4){
          plat[i][j] = NOIR;
        }else if(i == 3 && j == 4 || i == 4 && j == 3){
          plat[i][j] = BLANC;
        }else{
          plat[i][j] = " ";
        }
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
