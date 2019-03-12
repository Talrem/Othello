#include "../definitions.h"

int prise(int tab[],char * plat[TAILLE][TAILLE],int ligne, int colonne, char * couleur, int direction);
int checkTableau(int tab[],char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur,int direction);
int initTableau(int tab[]);
int prendPion(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur);
int estInvalide(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur);
void saisieCoupJcIA(char * plat[TAILLE][TAILLE], char * couleur, int nbTours, int difficulte);
void saisieCoupJcJD(char * plat[TAILLE][TAILLE], char * couleur, int nbTours);
void saisieCoupJcJL(char * plat[TAILLE][TAILLE],char * couleur, int nbTours);
