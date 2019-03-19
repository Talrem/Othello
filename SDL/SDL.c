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

         break;
      }
   }

   SDL_DestroyRenderer(pRenderer);
   SDL_DestroyWindow(pWindow);
}
