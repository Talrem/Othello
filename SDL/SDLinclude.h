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

SDL_Window* showWindow();
int creerBoutons(SDL_Window * pWindow, int nbBouton, ...);

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
int SDL_AfficherErreur(SDL_Renderer * pRenderer, char * error[], int nbErreur, int posXError, int posYError, int taillePolice);

/*
*  Fonctions de jeu
*/
int jeuJCJ(SDL_Window * pWindow, SDL_Renderer * Renderer);
int jeuJCIAF(SDL_Window * pWindow, SDL_Renderer * Renderer);
int jeuJCIAM(SDL_Window * pWindow, SDL_Renderer * Renderer);
int jeuJCIAD(SDL_Window * pWindow, SDL_Renderer * Renderer);
