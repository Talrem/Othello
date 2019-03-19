#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <stdarg.h>
#include "../Init/init.h"
#include "../definitions.h"
#include "../Aff/aff.h"
#include "../Tour/tour.h"
#include "../SDL/definitionsSDL.h"
#include "../SDL/SDLinclude.h"

SDL_Window* showWindow(){

	SDL_Window *pWindow = NULL;

	/* Initialisation simple */
	if(SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stdout, "Echec de l'initialisation de SDL (%s)\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	/* Initialisation TTF */
	if(TTF_Init()){
		fprintf(stderr, "Erreur d'initialisation de TTF (%s)\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Othello",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													800,
													600,
													SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	return pWindow;
}

int creerBoutons(SDL_Window * pWindow, int nbBouton, ...){
   int posXBouton, posYBouton, widthBouton, heigthBouton;
	int window_w, window_h;
	SDL_GetWindowSize(pWindow, &window_w, &window_h);
	posXBouton = widthBouton = window_w / 3;
	posYBouton = window_h / 8;
	heigthBouton = window_h / 8;

	va_list valiste;
	SDL_Rect * bouton;
	int i;
	va_start(valiste, nbBouton);
	for(i = 0; i < nbBouton; i++){
		bouton = va_arg(valiste, SDL_Rect*);
		bouton->x =	posXBouton;
		bouton->y = posYBouton * (1 + i) + (i * 10);
		bouton->w = widthBouton;
		bouton->h = heigthBouton;
	}

	va_end(valiste);
	return 1;
}

int SDL_Menu1(SDL_Window * pWindow, SDL_Renderer * pRenderer){
   if(pWindow){
		int nbBouton = 4;
		SDL_Rect tabBouton[nbBouton];
		creerBoutons(pWindow, nbBouton, &(tabBouton[0]), &(tabBouton[1]), &(tabBouton[2]), &(tabBouton[3]));
      int running = 1;

		SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);

      while(running){
         SDL_Event e;
         while(SDL_PollEvent(&e)){
            switch(e.type){
               case SDL_QUIT: running = 0;
                  return 0; break;
               case SDL_WINDOWEVENT:
                  switch(e.window.event){
                     case SDL_WINDOWEVENT_EXPOSED:
                     case SDL_WINDOWEVENT_SIZE_CHANGED:
                     case SDL_WINDOWEVENT_RESIZED:
                        //Si la fenetre est redimensionnée, on réaffiche tout
								SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);
                     case SDL_WINDOWEVENT_SHOWN:
                        SDL_SetRenderDrawColor(pRenderer, COULEUR_BLANC);
                        SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);

                        SDL_RenderPresent(pRenderer);
                     break;
                  }
            }
         }
      }
   }
   return 1;
}

int SDL_AfficherMenu1(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton){
	SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
	SDL_RenderClear(pRenderer);
	creerBoutons(pWindow, nbBouton, &(tabBouton[0]), &(tabBouton[1]), &(tabBouton[2]), &(tabBouton[3]));
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BLANC);
	SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);
	SDL_RenderPresent(pRenderer);

	return 0;
}
