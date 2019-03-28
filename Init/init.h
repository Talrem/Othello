#include "../definitions.h"

void initPlat(char * plat[TAILLE][TAILLE]);
void initTestRand(char * plat[TAILLE][TAILLE]);
void initTestVide(char * plat[TAILLE][TAILLE]);
int initPlatFic(char * plat[TAILLE][TAILLE], FILE * fichier);
int savePartie(char * plat[TAILLE][TAILLE], FILE * fichier, int nbTours);
void initTestPasDeNoir(char * plat[TAILLE][TAILLE]);
void initTestPasDeBlanc(char * plat[TAILLE][TAILLE]);
void initTestPlein(char * plat[TAILLE][TAILLE]);
