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

         running = SDL_Menu1(pWindow, pRenderer);
      }
   }

   SDL_DestroyRenderer(pRenderer);
   SDL_DestroyWindow(pWindow);
}
