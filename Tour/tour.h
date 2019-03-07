#include "../definitions.h"

int checkTableau(int tab[]);
int initTableau(int tab[]);
int prendPion(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur);
int estValide(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur);
void saisieCoupJcID(char * plat[TAILLE][TAILLE], char * couleur);
void saisieCoupJcII(char * plat[TAILLE][TAILLE], char * couleur);
void saisieCoupJcIF(char * plat[TAILLE][TAILLE], char * couleur);
void saisieCoupJcJD(char * plat[TAILLE][TAILLE], char * couleur);
void saisieCoupJcJL(char * plat[TAILLE][TAILLE],char * couleur);
