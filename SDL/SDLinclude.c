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
#include "../TestSDL/SDL_Othello.h"

int SDL_AfficherMenu1(SDL_Window * pWindow, SDL_Renderer * pRenderer){
   int posXBouton, posYBouton, widthBouton, lengthBouton;

   if(pWindow){
      SDL_Event e;
      while(SDL_PollEvent(&e)){
         switch(e.type){
            case SDL_QUIT: running = 0;
               break;
            case SDL_WINDOWEVENT:
               case SDL_WINDOWEVENT_EXPOSED:
               case SDL_WINDOWEVENT_SIZE_CHANGED:
               case SDL_WINDOWEVENT_RESIZED:
                  //Si la fenetre est redimensionnée, on réaffiche tout
                  SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
                  SDL_RenderClear(pRenderer);

                  SDL_RenderPresent(pRenderer);
               case SDL_WINDOWEVENT_SHOWN: break;
         }
      }
   }
}
