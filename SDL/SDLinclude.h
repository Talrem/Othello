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
int SDL_Menu1(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int creerBoutons(SDL_Window * pWindow, int nbBouton, ...);
int SDL_AfficherMenu1(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton);
int SDL_Menu2(SDL_Window * pWindow, SDL_Renderer * pRenderer);
int SDL_AfficherMenu2(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton);
