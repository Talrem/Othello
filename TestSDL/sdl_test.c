#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int main(int argc, char const *argv[]) {
   SDL_Window *pWindow = NULL; //Le pointeur vers la surface incluse dans la fenetre
   SDL_Surface *texte = NULL, *image = NULL;
   SDL_Renderer * renderer = NULL ;
   SDL_Rect txtDestRect ,imgDestRect ;
   TTF_Font *police = NULL; //Le pointeur vers notre police
   SDL_Color couleurNoire = {0, 0, 0}; //Une variable de couleur noire
   if(SDL_Init(SDL_INIT_VIDEO) == -1){
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
   }
   if(TTF_Init() == -1){
      fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
      exit(EXIT_FAILURE);
   }

   //FENETRE
   pWindow = SDL_CreateWindow("LA FENETRE AAAAAAAAAAAAAAAA", //Nom de la fenetre
                              SDL_WINDOWPOS_UNDEFINED, //posX sur l'écran
                              SDL_WINDOWPOS_UNDEFINED, //posY sur l'écran
                              1000, //Dimension X
                              500, //Dimension Y
                              SDL_SWSURFACE | SDL_WINDOW_RESIZABLE); //Options
   if(!pWindow){
      fprintf(stderr,"Erreur a la creation de la fenetre : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
   }

   //RENDERER
   renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
   if(renderer == NULL){
      fprintf(stderr, "Erreur a la creation du renderer\n");
      exit(EXIT_FAILURE);
   }
   if((police = TTF_OpenFont("./Minecraft.ttf", 24)) == NULL){
      fprintf(stderr, "erreur chargement font\n");
      exit(EXIT_FAILURE);
   }

   //TEXTE
   texte = TTF_RenderUTF8_Blended(police, "Minecraft !", couleurNoire);
   if(!texte){
      fprintf(stderr, "Erreur a la creation du texte : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
   }
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
   if(!texte_tex){
      fprintf(stderr, "Erreur a la creation du rendu du texte : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
   }
   SDL_FreeSurface(texte);
   /*Position ou sera mis le texte dans la fenetre */
   txtDestRect.x = txtDestRect.y = 10;
   SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));

   //IMAGE
   //load sample.png into image
   SDL_RWops *rwop = SDL_RWFromFile("./Umaru.png", "rb");
   image = IMG_LoadPNG_RW(rwop);
   if(!image){
         printf("IMG_LoadPNG_RW : %s\n", IMG_GetError());
   }
   SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, image);
   if(!image_tex){
      fprintf(stderr, "Erreur a la creation du rendu de l ’ image : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
   }
   SDL_FreeSurface(image); /* on a la texture , plus besoin de l ’ image */

   int i, j;
   char truc[10];
   //CREATION DE LA FENETRE
   if(pWindow){
      int running = 1;
      while(running){
         SDL_Event e;
         while(SDL_PollEvent(&e)){
            switch(e.type){
               case SDL_QUIT: running = 0;
                  break ;
               case SDL_WINDOWEVENT:
               switch(e.window.event){
                  case SDL_WINDOWEVENT_EXPOSED:
                  case SDL_WINDOWEVENT_SIZE_CHANGED:
                  case SDL_WINDOWEVENT_RESIZED:
                  case SDL_WINDOWEVENT_SHOWN:
                     /* Le fond de la fenetre sera blanc */
                     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                     SDL_RenderClear(renderer);
                     /* Ajout du texte en noir */
                     SDL_GetWindowSize(pWindow, &i, &j);
                     sprintf(truc, "%d x %d", i, j);
                     texte = TTF_RenderUTF8_Blended(police, truc, couleurNoire);
                     texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
                     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                     SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
                     /* Ajout de l'image a une c e r t a i n e p o s i t i o n */
                     /*imgDestRect.x = imgDestRect.y = 50;
                     SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
                     SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);*/
                     /* On fait le rendu ! */
                     SDL_RenderPresent(renderer);
                     break ;
               }
                  break ;
            }
         }
      }
   } else {
      fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
   }

   SDL_DestroyWindow(pWindow);
   TTF_CloseFont(police); /*Doit etre avant TTF_Quit()*/
   TTF_Quit();
   SDL_Quit();
   return EXIT_SUCCESS;
}
