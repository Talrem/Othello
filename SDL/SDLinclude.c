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
#include "../SDL/SDL_Othello.h"

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
	return 0;
}

int SDL_Menu1(SDL_Window * pWindow, SDL_Renderer * pRenderer){
   if(pWindow){

		int nbBouton = 4;
		SDL_Rect tabBouton[nbBouton];
		//creerBoutons(pWindow, nbBouton, &(tabBouton[0]), &(tabBouton[1]), &(tabBouton[2]), &(tabBouton[3]));
		/*
		* bouton 0 -> menu 2
		* bouton 1 -> menu 3
		* bouton 2 -> menu 4 ?
		* bouton 3 -> Quitter
		*/
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
                     case SDL_WINDOWEVENT_SHOWN:
								SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);
                     break;
                  }
					case SDL_MOUSEBUTTONDOWN:
						//on vérifie sur quel bouton on clique :
						//puis on appel la fonction qui permet de changer de menu
						if(posClick(e.button, tabBouton[0].x, tabBouton[0].y, (tabBouton[0].x + tabBouton[0].w), (tabBouton[0].y + tabBouton[0].h))){ //bouton 1
							SDL_Menu2(pWindow, pRenderer);
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[1].x, tabBouton[1].y, (tabBouton[1].x + tabBouton[1].w), (tabBouton[1].y + tabBouton[1].h))){ //bouton 2
							printf("Bouton 2\n");
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[2].x, tabBouton[2].y, (tabBouton[2].x + tabBouton[2].w), (tabBouton[2].y + tabBouton[2].h))){ //bouton 3
							printf("Bouton 3\n");
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[3].x, tabBouton[3].y, (tabBouton[3].x + tabBouton[3].w), (tabBouton[3].y + tabBouton[3].h))){ //bouton 4
							printf("Bouton 4\n");
							//Ce boutton sert a quitter, donc running a 0
							running = 0;
						}
            }
         }
      }
   }
   return 0;
}

int SDL_AfficherMenu1(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton){
	SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
	SDL_RenderClear(pRenderer);
	creerBoutons(pWindow, nbBouton, &(tabBouton[0]), &(tabBouton[1]), &(tabBouton[2]), &(tabBouton[3]));
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BLANC);
	SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);
	int window_w; SDL_GetWindowSize(pWindow, &window_w, NULL); int policeSize = window_w / 22;
	drawText(pRenderer, (tabBouton[0].x + tabBouton[0].x / 20), (tabBouton[0].y + tabBouton[0].y / 4), "1 joueur", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[1].x + tabBouton[1].x / 20), (tabBouton[1].y + tabBouton[0].y / 4), "2 joueur", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[2].x + tabBouton[2].x / 20), (tabBouton[2].y + tabBouton[0].y / 4), "Options", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[3].x + tabBouton[3].x / 20), (tabBouton[3].y + tabBouton[0].y / 4), "Quitter", policeSize, COULEUR_NOIR);
	SDL_RenderPresent(pRenderer);

	return 0;
}

int SDL_Menu2(SDL_Window * pWindow, SDL_Renderer * pRenderer){
	if(pWindow){

		int nbBouton = 3;
		SDL_Rect tabBouton[nbBouton];
		SDL_AfficherMenu2(pWindow, pRenderer, tabBouton, nbBouton);

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
                     case SDL_WINDOWEVENT_SHOWN:
								SDL_AfficherMenu2(pWindow, pRenderer, tabBouton, nbBouton);
                     break;
                  }
					case SDL_MOUSEBUTTONDOWN:
						//on vérifie sur quel bouton on clique :
						//puis on appel la fonction qui permet de changer de menu
						if(posClick(e.button, tabBouton[0].x, tabBouton[0].y, (tabBouton[0].x + tabBouton[0].w), (tabBouton[0].y + tabBouton[0].h))){ //bouton 1
							SDL_Menu2a(pWindow, pRenderer);
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu2(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[1].x, tabBouton[1].y, (tabBouton[1].x + tabBouton[1].w), (tabBouton[1].y + tabBouton[1].h))){ //bouton 2
							printf("Continuer\n");
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu2(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[2].x, tabBouton[2].y, (tabBouton[2].x + tabBouton[2].w), (tabBouton[2].y + tabBouton[2].h))){ //bouton 3
							printf("Retour\n");
							//Ce bouton sert a faire retour
							return 0;
						}
            }
         }
		}

		return 0;
	}
}

int SDL_AfficherMenu2(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton){
	SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
	SDL_RenderClear(pRenderer);
	creerBoutons(pWindow, nbBouton, &(tabBouton[0]), &(tabBouton[1]), &(tabBouton[2]), &(tabBouton[3]));
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BLANC);
	SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);
	int window_w; SDL_GetWindowSize(pWindow, &window_w, NULL); int policeSize = window_w / 22;
	drawText(pRenderer, (tabBouton[0].x + tabBouton[0].x / 20), (tabBouton[0].y + tabBouton[0].y / 4), "Nouvelle Partie", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[1].x + tabBouton[1].x / 20), (tabBouton[1].y + tabBouton[0].y / 4), "Continuer", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[2].x + tabBouton[2].x / 20), (tabBouton[2].y + tabBouton[0].y / 4), "Retour", policeSize, COULEUR_NOIR);
	SDL_RenderPresent(pRenderer);

	return 0;
}

int SDL_Menu2a(SDL_Window * pWindow, SDL_Renderer * pRenderer){
	if(pWindow){
		int nbBouton = 4;
		SDL_Rect tabBouton[nbBouton];
		SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);

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
                     case SDL_WINDOWEVENT_SHOWN:
								SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);
                     break;
                  }
					case SDL_MOUSEBUTTONDOWN:
						//on vérifie sur quel bouton on clique :
						//puis on appel la fonction qui permet de changer de menu
						if(posClick(e.button, tabBouton[0].x, tabBouton[0].y, (tabBouton[0].x + tabBouton[0].w), (tabBouton[0].y + tabBouton[0].h))){ //bouton 1
							printf("Facile\n");
							//Lance l'IA facile. O réaffiche le menu une fois la partie finie
							SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[1].x, tabBouton[1].y, (tabBouton[1].x + tabBouton[1].w), (tabBouton[1].y + tabBouton[1].h))){ //bouton 2
							printf("Moyen\n");
							//Lance l'IA moyenne. O réaffiche le menu une fois la partie finie
							SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[2].x, tabBouton[2].y, (tabBouton[2].x + tabBouton[2].w), (tabBouton[2].y + tabBouton[2].h))){
							printf("Difficile\n");
							//Lance l'IA Difficile. O réaffiche le menu une fois la partie finie
							SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);
						}else if(posClick(e.button, tabBouton[3].x, tabBouton[3].y, (tabBouton[3].x + tabBouton[3].w), (tabBouton[3].y + tabBouton[3].h))){ //bouton 3
							printf("Retour\n");
							//Ce bouton sert a faire retour
							return 0;
						}
            }
         }
		}

		return 0;
	}
}

int SDL_AfficherMenu2a(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton){
	SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
	SDL_RenderClear(pRenderer);
	creerBoutons(pWindow, nbBouton, &(tabBouton[0]), &(tabBouton[1]), &(tabBouton[2]), &(tabBouton[3]), &(tabBouton[4]));
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BLANC);
	SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);
	int window_w; SDL_GetWindowSize(pWindow, &window_w, NULL); int policeSize = window_w / 22;
	drawText(pRenderer, (tabBouton[0].x + tabBouton[0].x / 20), (tabBouton[0].y + tabBouton[0].y / 4), "Facile", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[1].x + tabBouton[1].x / 20), (tabBouton[1].y + tabBouton[0].y / 4), "Normal", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[2].x + tabBouton[2].x / 20), (tabBouton[2].y + tabBouton[0].y / 4), "Difficile", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[3].x + tabBouton[3].x / 20), (tabBouton[3].y + tabBouton[0].y / 4), "Difficile", policeSize, COULEUR_NOIR);
	SDL_RenderPresent(pRenderer);

	return 0;
}
