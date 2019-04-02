#include "./init.h"

void initTestVide(char * plat[TAILLE][TAILLE]){
  for(int i = 0; i < TAILLE;i++){
     for(int j = 0; j < TAILLE;j++){
       plat[i][j] = " ";
     }
  }
}

void initPlat(char * plat[TAILLE][TAILLE]){
  initTestVide(plat);
   for(int i = 0; i < TAILLE;i++){
      for(int j = 0; j < TAILLE;j++){
        if((i == 3 && j == 3) || (i == 4 && j == 4)){
          plat[i][j] = NOIR;
        }else if((i == 3 && j == 4) || (i == 4 && j == 3)){
          plat[i][j] = BLANC;
        }else{
          plat[i][j] = " ";
        }
      }
   }
}

int initPlatFic(char * plat[TAILLE][TAILLE], FILE * fichier, char ** tour){
  if(!fichier) return 1;
  int val;
  int nbTours;
  char tourActuel;
  fscanf(fichier,"%d",&nbTours);
  for(int i = 0; i < TAILLE ; i++){
    for(int j = 0; j < TAILLE ; j++){
      fscanf(fichier,"%d",&val);
      switch (val) {
        case 2:
          plat[i][j] = NOIR;
          break;
        case 1:
          plat[i][j] = BLANC;
          break;
        default:
          plat[i][j] = VIDE;
          break;
      }
    }
  }
  fscanf(fichier,"%c",&tourActuel);
  if(tourActuel == 'n'){
    *tour = NOIR;
  }else{
    *tour = BLANC;
  }
  return nbTours;
}

int savePartie(char * plat[TAILLE][TAILLE], FILE * fichier, int nbTours, char * tour){
  if(!fichier) return 1;
  fprintf(fichier,"%d ",nbTours);
  for(int i = 0; i < TAILLE ; i++){
    for(int j = 0; j < TAILLE ; j++){
      if(!strcmp(plat[i][j],NOIR)){
        fprintf(fichier,"%d ",2);
      }else if(!strcmp(plat[i][j],BLANC)){
        fprintf(fichier,"%d ",1);
      }else{
        fprintf(fichier,"%d ",0);
      }
    }
  }
  if(tour == NOIR){
    fprintf(fichier,"n ");
  }else{
    fprintf(fichier,"b ");
  }
  return 0;
}

void initTestPasDeNoir(char * plat[TAILLE][TAILLE]){
  initTestVide(plat);
  for(int i = 0; i < TAILLE;i++){
     for(int j = 0; j < TAILLE;j++){
       switch(rand()%2){
          case 0: plat[i][j] = BLANC; break;
          default:break;
       }
     }
  }
}

void initTestPasDeBlanc(char * plat[TAILLE][TAILLE]){
  initTestVide(plat);
  for(int i = 0; i < TAILLE;i++){
     for(int j = 0; j < TAILLE;j++){
       switch(rand()%2){
          case 0: plat[i][j] = NOIR; break;
          default:break;
       }
     }
  }
}

void initTestPlein(char * plat[TAILLE][TAILLE]){
  initTestVide(plat);
  for(int i = 0; i < TAILLE;i++){
     for(int j = 0; j < TAILLE;j++){
        switch(rand()%2){
           case 0: plat[i][j] = NOIR; break;
           case 1: plat[i][j] = BLANC; break;
           default:break;
        }
     }
  }
}

void initTestRand(char * plat[TAILLE][TAILLE]){
  initTestVide(plat);
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
