#include "../definitions.h"

int prise(int tab[],char * plat[TAILLE][TAILLE],int ligne, int colonne, char * couleur, int direction);
int checkTableau(int tab[],char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur,int direction, int estTest);
void initTableau(int tab[]);
int prendPion(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur, int estTest);
int aVoisins(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur);
int estInvalide(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur, int estTest);
int coupAleatIA(char * plat[TAILLE][TAILLE],char * couleur);
int coupIntellIA(char * plat[TAILLE][TAILLE],char * couleur);
void saisieCoupJcJL(char * plat[TAILLE][TAILLE],char * couleur, int nbTours);
void saisieCoupJcIA(char * plat[TAILLE][TAILLE], char * couleur, int nbTours, int difficulte, int couleurIA);
void saisieCoupJcJD(char * plat[TAILLE][TAILLE], char * couleur, int nbTours, int coupDonnee[2]);
int estFinie(char * plat[TAILLE][TAILLE]);
int coupPossible(char * plat[TAILLE][TAILLE] ,char * couleur);
void caseJouable(char * plat[TAILLE][TAILLE] ,char * couleur,int abs[MAX_C],int ord[MAX_C]);
int NbrcoupPossible(char * plat[TAILLE][TAILLE] ,char * couleur);
int NbrpionsPlat(int nbTours);
char convertEtoL(int indice);
void evaluation(int abs[MAX_C],int ord[MAX_C],int eval[MAX_C],int nbrcp);
