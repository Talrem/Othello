#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "../Init/init.h"
#include "../definitions.h"
#include "../Aff/aff.h"
#include "../Tour/tour.h"
#include "../definitions.h"
#include "../SDL/definitionsSDL.h"

#define COULEUR_BOUTON 147, 0, 24, 0

typedef struct s_dimension{
   char * res;
   int w, h;
} t_dimension;

SDL_Window* showWindow();
int creerBoutons(SDL_Window * pWindow, int nbBouton, ...);
int getRes(SDL_Window * pWindow, t_dimension resolution[], int nbRes);
void initBoutonMenu4(SDL_Window * pWindow, SDL_Rect * bouton, SDL_Rect * boutonDroit, SDL_Rect * boutonGauche, SDL_Rect * appliquer);


/*
*  Fonctions d'affichage des menus
*/
int SDL_Menu1(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int SDL_AfficherMenu1(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton);
int SDL_Menu2(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int SDL_AfficherMenu2(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton);
int SDL_Menu2a(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int SDL_AfficherMenu2a(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton);
int SDL_Menu3(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int SDL_AfficherMenu3(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton);
int SDL_Menu4(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int SDL_AfficherMenu4(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton, t_dimension resolution[], int nbRes, int resAct);
int SDL_MenuPause(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int SDL_AfficherMenuPause(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton);
int SDL_AfficherErreur(SDL_Renderer * pRenderer, char * error[], int nbErreur, int posXError, int posYError, int taillePolice);
int SDL_AfficherJoueurTour(SDL_Renderer * pRenderer, int x, int y, int radius, int taillePolice, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int SDL_AfficherBoutonMenuPause(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect bouton);
/*
*  Fonctions de jeu
*/
int jeuJCJ(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int jeuJCIA(SDL_Window * pWindow, SDL_Renderer * pRenderer, int difficulte);
