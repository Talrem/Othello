#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "Init/init.h"
#include "definitions.h"
#include "Aff/aff.h"
#include "Tour/tour.h"
#include "SDL/definitionsSDL.h"
#include "SDL/SDLinclude.h"

int main(){
   //Creation de la fenetre
   SDL_Window * pWindow = NULL;
   pWindow = showWindow();

   //Creation du renderer
   SDL_Renderer * pRenderer = NULL;
   pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

   if(pWindow){
      int running = 1;
      while(running){
         //On attend un peu a chaque tour de boucler pour éviter trop d'execution
         SDL_Delay(1);

         //On dessine le fond de la fenetre, il ne change pas de toute l'execution
         SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
         SDL_RenderClear(pRenderer);
         SDL_RenderPresent(pRenderer);

         SDL_Event e;
         while(SDL_PollEvent(&e)){
            switch(e.type){
               case SDL_QUIT: running = 0;
						break;
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
                        running = SDL_AfficherMenu1(pWindow, pRenderer);
                        break;
                  }
            }
         }
      }
   }

   SDL_DestroyRenderer(pRenderer);
   SDL_DestroyWindow(pWindow);
}
