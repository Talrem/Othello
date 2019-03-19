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
#include "../SDL/definitionsSDL.h"

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

int SDL_AfficherMenu1(SDL_Window * pWindow, SDL_Renderer * pRenderer){
   if(pWindow){

      int posXBouton, posYBouton, widthBouton, heigthBouton;
      int window_w, window_h;

      SDL_GetWindowSize(pWindow, &window_w, &window_h);
      posXBouton = widthBouton = window_w / 3;
      posYBouton = window_h / 4;
      heigthBouton = posYBouton / 2;

      SDL_Rect boutonMenu1 =  {posXBouton, posYBouton, widthBouton, heigthBouton};

      int running = 1;
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
                        SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
                        SDL_RenderClear(pRenderer);

                        SDL_RenderPresent(pRenderer);
                     case SDL_WINDOWEVENT_SHOWN:
                        SDL_SetRenderDrawColor(pRenderer, COULEUR_BLANC);
                        SDL_RenderFillRect(pRenderer, &boutonMenu1);

                        SDL_RenderPresent(pRenderer);
                     break;
                  }
            }
         }
      }
   }
   return 1;
}
