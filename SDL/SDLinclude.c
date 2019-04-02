#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
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

int getRes(SDL_Window * pWindow, t_dimension resolution[], int nbRes){
	int w, h;
	SDL_GetWindowSize(pWindow, &w, &h);
	int i;
	for(i = 0; i < (nbRes - 1); i++){
		if(resolution[i].w == w && resolution[i].h == h) return i;
	}
	return i;
}

void initBoutonMenu4(SDL_Window * pWindow, SDL_Rect * bouton, SDL_Rect * boutonDroite, SDL_Rect * boutonGauche, SDL_Rect * appliquer){
	int window_w, window_h;
	SDL_GetWindowSize(pWindow, &window_w, &window_h);

	bouton->x = (window_w / 3);
	bouton->y = (window_h / 3);
	bouton->w = (window_w / 3);
	bouton->h = (window_h / 8);

	boutonDroite->x = (bouton->x + bouton->w + 5);
	boutonDroite->y = (bouton->y);
	boutonDroite->w = (bouton->h);
	boutonDroite->h = (bouton->h);

	boutonGauche->x = (bouton->x - bouton->h - 5);
	boutonGauche->y = (bouton->y);
	boutonGauche->w = (bouton->h);
	boutonGauche->h = (bouton->h);

	appliquer->x = (bouton->x);
	appliquer->y = (bouton->y + bouton->h + 5);
	appliquer->w = (bouton->w);
	appliquer->h = (bouton->h);
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

		int retour = 0;

		SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);

      while(running){
			SDL_Delay(1);

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
							SDL_RenderClear(pRenderer);
							retour = SDL_Menu2(pWindow, pRenderer);
							if(retour == -1) return -1;
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[1].x, tabBouton[1].y, (tabBouton[1].x + tabBouton[1].w), (tabBouton[1].y + tabBouton[1].h))){ //bouton 2
							SDL_RenderClear(pRenderer);
							retour = SDL_Menu3(pWindow, pRenderer);
							if(retour == -1) return -1;
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[2].x, tabBouton[2].y, (tabBouton[2].x + tabBouton[2].w), (tabBouton[2].y + tabBouton[2].h))){ //bouton 3
							retour = SDL_Menu4(pWindow, pRenderer);
							if(retour == -1) return -1;
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu1(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[3].x, tabBouton[3].y, (tabBouton[3].x + tabBouton[3].w), (tabBouton[3].y + tabBouton[3].h))){ //bouton 4
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
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BOUTON);
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

		int retour = 0;

		int running = 1;
		while(running){
			SDL_Delay(1);

			SDL_Event e;
         while(SDL_PollEvent(&e)){
            switch(e.type){
					case SDL_QUIT: running = 0;
                  return -1; break;
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
							SDL_RenderClear(pRenderer);
							retour = SDL_Menu2a(pWindow, pRenderer);
							if(retour == -1) return -1;
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu2(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[1].x, tabBouton[1].y, (tabBouton[1].x + tabBouton[1].w), (tabBouton[1].y + tabBouton[1].h))){ //bouton 2
							printf("Continuer\n");
							//si on reviens ici, c'est que l'utilisateur a fait retour, il faut reafficher le menu
							SDL_AfficherMenu2(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[2].x, tabBouton[2].y, (tabBouton[2].x + tabBouton[2].w), (tabBouton[2].y + tabBouton[2].h))){ //bouton 3
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
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BOUTON);
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

		int nbBouton = 5;
		SDL_Rect tabBouton[nbBouton];
		SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);

		int retour = 0;

		int running = 1;
		while(running){
			SDL_Delay(1);

			SDL_Event e;
         while(SDL_PollEvent(&e)){
            switch(e.type){
					case SDL_QUIT: running = 0;
                  return -1; break;
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
							jeuJCIA(pWindow, pRenderer, 1);
							//Lance l'IA facile. O réaffiche le menu une fois la partie finie
							SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[1].x, tabBouton[1].y, (tabBouton[1].x + tabBouton[1].w), (tabBouton[1].y + tabBouton[1].h))){ //bouton 2
							jeuJCIA(pWindow, pRenderer, 3);
							//Lance l'IA moyenne. O réaffiche le menu une fois la partie finie
							SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[2].x, tabBouton[2].y, (tabBouton[2].x + tabBouton[2].w), (tabBouton[2].y + tabBouton[2].h))){
							jeuJCIA(pWindow, pRenderer, 10);
							//Lance l'IA Difficile. O réaffiche le menu une fois la partie finie
							SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);
						}else if(posClick(e.button, tabBouton[3].x, tabBouton[3].y, (tabBouton[3].x + tabBouton[3].w), (tabBouton[3].y + tabBouton[3].h))){ //bouton 3
							jeuJCIA(pWindow, pRenderer, 70);
							//Lance l'IA en Ultra. Réaafiche le menu une fois la partie finie
							SDL_AfficherMenu2a(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[4].x, tabBouton[4].y, (tabBouton[4].x + tabBouton[4].w), (tabBouton[4].y + tabBouton[4].h))){ //bouton 4
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
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BOUTON);
	SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);
	int window_w; SDL_GetWindowSize(pWindow, &window_w, NULL); int policeSize = window_w / 22;
	drawText(pRenderer, (tabBouton[0].x + tabBouton[0].x / 20), (tabBouton[0].y + tabBouton[0].y / 4), "Facile", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[1].x + tabBouton[1].x / 20), (tabBouton[1].y + tabBouton[0].y / 4), "Normal", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[2].x + tabBouton[2].x / 20), (tabBouton[2].y + tabBouton[0].y / 4), "Difficile", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[3].x + tabBouton[3].x / 20), (tabBouton[3].y + tabBouton[0].y / 4), "Ultra", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[4].x + tabBouton[4].x / 20), (tabBouton[4].y + tabBouton[0].y / 4), "Retour", policeSize, COULEUR_NOIR);
	SDL_RenderPresent(pRenderer);

	return 0;
}

int SDL_Menu3(SDL_Window * pWindow, SDL_Renderer * pRenderer){
	if(pWindow){

		int nbBouton = 3;
		SDL_Rect tabBouton[nbBouton];
		SDL_AfficherMenu3(pWindow, pRenderer, tabBouton, nbBouton);

		int retour = 0;

		int running = 1;
		while(running){
			SDL_Delay(1);

			SDL_Event e;
         while(SDL_PollEvent(&e)){
            switch(e.type){
					case SDL_QUIT: running = 0;
                  return -1; break;
					case SDL_WINDOWEVENT:
                  switch(e.window.event){
                     case SDL_WINDOWEVENT_EXPOSED:
                     case SDL_WINDOWEVENT_SIZE_CHANGED:
                     case SDL_WINDOWEVENT_RESIZED:
                     case SDL_WINDOWEVENT_SHOWN:
								SDL_AfficherMenu3(pWindow, pRenderer, tabBouton, nbBouton);
                     break;
                  }
					case SDL_MOUSEBUTTONDOWN:
						//on vérifie sur quel bouton on clique :
						//puis on appel la fonction qui permet de changer de menu
						if(posClick(e.button, tabBouton[0].x, tabBouton[0].y, (tabBouton[0].x + tabBouton[0].w), (tabBouton[0].y + tabBouton[0].h))){ //bouton 1
							SDL_RenderClear(pRenderer);
							retour = jeuJCJ(pWindow, pRenderer);
							if(retour == -1) return -1; //Retour de quitter
							SDL_AfficherMenu3(pWindow, pRenderer, tabBouton, nbBouton);
						} else if(posClick(e.button, tabBouton[1].x, tabBouton[1].y, (tabBouton[1].x + tabBouton[1].w), (tabBouton[1].y + tabBouton[1].h))){ //bouton 2
							printf("Continuer\n");
							//Lance l'IA moyenne. O réaffiche le menu une fois la partie finie
							SDL_AfficherMenu3(pWindow, pRenderer, tabBouton, nbBouton);
						}else if(posClick(e.button, tabBouton[2].x, tabBouton[2].y, (tabBouton[2].x + tabBouton[2].w), (tabBouton[2].y + tabBouton[2].h))){ //bouton 3
							//Ce bouton sert a faire retour
							return 0;
						}
            }
         }
		}

		return 0;
	}
}

int SDL_AfficherMenu3(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton){
	SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
	SDL_RenderClear(pRenderer);
	creerBoutons(pWindow, nbBouton, &(tabBouton[0]), &(tabBouton[1]), &(tabBouton[2]));
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BOUTON);
	SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);
	int window_w; SDL_GetWindowSize(pWindow, &window_w, NULL); int policeSize = window_w / 22;
	drawText(pRenderer, (tabBouton[0].x + tabBouton[0].x / 20), (tabBouton[0].y + tabBouton[0].y / 4), "Nouvelle partie", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[1].x + tabBouton[1].x / 20), (tabBouton[1].y + tabBouton[0].y / 4), "Continuer", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[2].x + tabBouton[2].x / 20), (tabBouton[2].y + tabBouton[0].y / 4), "Retour", policeSize, COULEUR_NOIR);
	SDL_RenderPresent(pRenderer);

	return 0;
}

int SDL_Menu4(SDL_Window * pWindow, SDL_Renderer * pRenderer){
	if(pWindow){
		SDL_DisplayMode display;
		SDL_GetDesktopDisplayMode(0, &display);
		int w = display.w; //largeur et hauteur de l'écran (pas la fenetre)
		int h = display.h;

		int nbRes = 6;
		t_dimension verylow = {"640*480", 640, 480};
		t_dimension low = {"800*600", 800, 600};
		t_dimension medium = {"1024*768", 1024, 768};
		t_dimension high = {"1600*1200", 1600, 1200};
		t_dimension veryhigh = {"1920*1080", 1920, 1080};
		t_dimension custom = {"custom", 0, 0};
		t_dimension resolution[] = {verylow, low, medium, high, veryhigh, custom};
		int resAct = getRes(pWindow, resolution, nbRes);

		int window_w, window_h;
		SDL_GetWindowSize(pWindow, &window_w, &window_h);

		int nbBouton = 4;
		SDL_Rect bouton;
		SDL_Rect boutonDroite;
		SDL_Rect boutonGauche;
		SDL_Rect appliquer;

		initBoutonMenu4(pWindow, &bouton, &boutonDroite, &boutonGauche, &appliquer);

		SDL_Rect tabBouton[] = {bouton, boutonDroite, boutonGauche, appliquer};

		SDL_AfficherMenu4(pWindow, pRenderer, tabBouton, nbBouton, resolution, nbRes, resAct);

		int running = 1;
		while(running){
			SDL_Delay(1);

			SDL_Event e;
         while(SDL_PollEvent(&e)){
            switch(e.type){
					case SDL_QUIT: running = 0;
                  return -1; break;
					case SDL_WINDOWEVENT:
                  switch(e.window.event){
                     case SDL_WINDOWEVENT_EXPOSED:
                     case SDL_WINDOWEVENT_SIZE_CHANGED:
                     case SDL_WINDOWEVENT_RESIZED:
                     case SDL_WINDOWEVENT_SHOWN:
								initBoutonMenu4(pWindow, &bouton, &boutonDroite, &boutonGauche, &appliquer);
								SDL_AfficherMenu4(pWindow, pRenderer, tabBouton, nbBouton, resolution, nbRes, resAct);
                     break;
                  }
					case SDL_MOUSEBUTTONDOWN:
						//on vérifie sur quel bouton on clique :
						//puis on appel la fonction qui permet de changer de menu
						if(posClick(e.button, boutonDroite.x, boutonDroite.y, (boutonDroite.x + boutonDroite.w), (boutonDroite.y + boutonDroite.h))){ //bouton Droite
							if(resAct < nbRes - 2) //empecher la selection de CUSTOM via les fleches
								resAct++;
							SDL_AfficherMenu4(pWindow, pRenderer, tabBouton, nbBouton, resolution, nbRes, resAct);
						} else if(posClick(e.button, boutonGauche.x, boutonGauche.y, (boutonGauche.x + boutonGauche.w), (boutonGauche.y + boutonGauche.h))){ //bouton Gauche
							if(resAct > 0) //empeche d'aller plus bas que 0 dans tab
								resAct--;
							SDL_AfficherMenu4(pWindow, pRenderer, tabBouton, nbBouton, resolution, nbRes, resAct);
						}else if(posClick(e.button, appliquer.x, appliquer.y, (appliquer.x + appliquer.w), (appliquer.y + appliquer.h))){ //bouton Retour
							//Ce bouton sert a faire appliquer la résolution et faire retour
							if(resolution[resAct].w <= w && resolution[resAct].h <= h){
								SDL_SetWindowSize(pWindow, resolution[resAct].w, resolution[resAct].h);
							} else {
								SDL_SetWindowSize(pWindow, w, h);
							}
							return 0;
						}
            }
         }
		}

		return 0;
	}
}

int SDL_AfficherMenu4(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton, t_dimension resolution[], int nbRes, int resAct){
	SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
	SDL_RenderClear(pRenderer);
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BOUTON);
	SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);
	int window_w; SDL_GetWindowSize(pWindow, &window_w, NULL); int policeSize = window_w / 22;
	drawText(pRenderer, tabBouton[0].x, tabBouton[0].y, resolution[resAct].res, policeSize, COULEUR_NOIR);
	drawText(pRenderer, tabBouton[1].x, tabBouton[1].y, ">", policeSize, COULEUR_NOIR);
	drawText(pRenderer, tabBouton[2].x, tabBouton[2].y, "<", policeSize, COULEUR_NOIR);
	drawText(pRenderer, tabBouton[3].x, tabBouton[3].y, "Appliquer", policeSize, COULEUR_NOIR);
	SDL_RenderPresent(pRenderer);
}

int SDL_MenuPause(SDL_Window * pWindow, SDL_Renderer * pRenderer){
	if(pWindow){

		int nbBouton = 3;
		SDL_Rect tabBouton[nbBouton];
		SDL_AfficherMenuPause(pWindow, pRenderer, tabBouton, nbBouton);

		int retour = 0;

		int running = 1;
		while(running){
			SDL_Delay(1);

			SDL_Event e;
         while(SDL_PollEvent(&e)){
            switch(e.type){
					case SDL_QUIT: running = 0;
                  return -1; break;
					case SDL_WINDOWEVENT:
                  switch(e.window.event){
                     case SDL_WINDOWEVENT_EXPOSED:
                     case SDL_WINDOWEVENT_SIZE_CHANGED:
                     case SDL_WINDOWEVENT_RESIZED:
                     case SDL_WINDOWEVENT_SHOWN:
								SDL_AfficherMenuPause(pWindow, pRenderer, tabBouton, nbBouton);
                     break;
                  }
					case SDL_MOUSEBUTTONDOWN:
						//on vérifie sur quel bouton on clique :
						//puis on appel la fonction qui permet de changer de menu
						if(posClick(e.button, tabBouton[0].x, tabBouton[0].y, (tabBouton[0].x + tabBouton[0].w), (tabBouton[0].y + tabBouton[0].h))){ //bouton 1
							return 1;
						} else if(posClick(e.button, tabBouton[1].x, tabBouton[1].y, (tabBouton[1].x + tabBouton[1].w), (tabBouton[1].y + tabBouton[1].h))){ //bouton 2
							printf("Sauvegarder\n");
							return 1;
						}else if(posClick(e.button, tabBouton[2].x, tabBouton[2].y, (tabBouton[2].x + tabBouton[2].w), (tabBouton[2].y + tabBouton[2].h))){ //bouton 3
							return -2;
						}
            }
         }
		}

		return 0;
	}
}

int SDL_AfficherMenuPause(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect * tabBouton, int nbBouton){
	creerBoutons(pWindow, nbBouton, &(tabBouton[0]), &(tabBouton[1]), &(tabBouton[2]));
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BOUTON);
	SDL_RenderFillRects(pRenderer, tabBouton, nbBouton);
	int window_w; SDL_GetWindowSize(pWindow, &window_w, NULL); int policeSize = window_w / 22;
	drawText(pRenderer, (tabBouton[0].x + tabBouton[0].x / 20), (tabBouton[0].y + tabBouton[0].y / 4), "Continuer", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[1].x + tabBouton[1].x / 20), (tabBouton[1].y + tabBouton[0].y / 4), "Sauvegarder", policeSize, COULEUR_NOIR);
	drawText(pRenderer, (tabBouton[2].x + tabBouton[2].x / 20), (tabBouton[2].y + tabBouton[0].y / 4), "Quitter", policeSize, COULEUR_NOIR);
	SDL_RenderPresent(pRenderer);

	return 0;
}

int SDL_AfficherErreur(SDL_Renderer * pRenderer, char * error[], int nbErreur, int posXError, int posYError, int taillePolice){
	if(nbErreur == 0)
		return 0;
	if(nbErreur <= 5){
	  drawText(pRenderer, posXError, posYError, "Le coup que vous avez voulu jouer", taillePolice, COULEUR_NOIR);
	  drawText(pRenderer, posXError, posYError + taillePolice + 5, error[nbErreur], taillePolice, COULEUR_NOIR);
  } else {
	  drawText(pRenderer, posXError, posYError + taillePolice + 5, error[nbErreur], taillePolice, COULEUR_NOIR);
  }
	return 0;
}

int SDL_AfficherJoueurTour(SDL_Renderer * pRenderer, int x, int y, int radius, int taillePolice, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	drawText(pRenderer, x, y, "Joueur :", taillePolice * 2, COULEUR_NOIR);
	afficherPion(pRenderer, x * 4, y * 7, radius, r, g, b, a);
	return 0;
}

int SDL_AfficherBoutonMenuPause(SDL_Window * pWindow, SDL_Renderer * pRenderer, SDL_Rect bouton){
	SDL_SetRenderDrawColor(pRenderer, COULEUR_BOUTON);
	SDL_RenderFillRect(pRenderer, &bouton);
	int window_w; SDL_GetWindowSize(pWindow, &window_w, NULL); int policeSize = window_w / 22;
	drawText(pRenderer, (bouton.x + bouton.w / 15), (bouton.y + bouton.h / 6), "Menu", policeSize, COULEUR_NOIR);

}

//Fonctions de jeu
int jeuJCJ(SDL_Window * pWindow, SDL_Renderer * pRenderer){
	if(pWindow){

		int window_w, window_h;

		/*Creation des variables du plateau : */
		int taillePlat, tailleCase, posXPlat, posYPlat;
		SDL_Rect plateau;
		SDL_Rect casePlateau;
		int radius;

		/*Creation de la matrice qui contient la disposition des pions*/
		char * plateauMat[TAILLE][TAILLE];
		initTestVide(plateauMat);
		initPlat(plateauMat);

		/*On défini le jouer qui commence*/
		char * joueur = NOIR;

		/*Position du texte d'erreur de coup*/
		int posXError, posYError;
		/*Taille de la police*/
		int taillePolice;
		/*Initialisation du tableau d'erreur*/
		char * coupOk = "";
		char * errorOut = "est en dehors du plateau.";
		char * errorNotEmpty = "n'est pas dans une case vide."; //dans la pratique, il ne sert pas
		char * errorNotNear = "n'est pas a cote d'une case adverse.";
		char * errorDontTake = "ne prend pas de pion adverse.";
		char * cantPlay = "Le joueur n'a pas pu jouer";
		char * error[6] = {coupOk, errorOut, errorNotEmpty, errorNotNear, errorDontTake, cantPlay};

		int posClicX, posClicY;

		int valide = 0;

		int posXJoueurTour, posYJoueurTour;

		/*Creation du bouton du menu*/
		SDL_Rect boutonMenuPause;

		/*Variable de test de quit*/
		int quitter = 0;

		/*On affiche le fond de la fenetre*/
		SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
		SDL_RenderClear(pRenderer);
		SDL_RenderPresent(pRenderer);

		while(!estFinie(plateauMat) && quitter != -2){

			/*On récupère la taille de la fenetre*/
			SDL_GetWindowSize(pWindow, &window_w, &window_h);

			/*Definition des variable du plateau*/
			calculVarPlat(pWindow, &taillePlat, &tailleCase, &posXPlat, &posYPlat, &plateau, &casePlateau);
			/*on calcule la taille d'un pion*/
			radius = tailleCase * 33 / 100;

			posXError = posXPlat;
			posYError = window_h / 60;
			taillePolice = window_w / 53;

			posXJoueurTour = window_w / 60;
			posYJoueurTour = window_h / 60;

			boutonMenuPause.x = window_w / 40;
			boutonMenuPause.y = window_h - window_h / 7;
			boutonMenuPause.w = window_w / 7;
			boutonMenuPause.h = window_h / 10;

			if(!coupPossible(plateauMat, joueur)){
				valide = 5;
				joueur = strcmp(joueur, NOIR) ? NOIR : BLANC;
			}

			SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
			SDL_RenderClear(pRenderer);
			/*On affiche la grille du plateau*/
			SDL_afficherPlateau(pRenderer, posXPlat, posYPlat, casePlateau, tailleCase);
			/*On affiche la matrice du plateau*/
			afficherMatrice(plateauMat, pRenderer, posXPlat, posYPlat, tailleCase, radius);
			/*On affiche l'erreur*/
			SDL_AfficherErreur(pRenderer, error, valide, posXError, posYError, taillePolice);
			/*On afficher le joueur du tour*/
			if(strcmp(joueur, NOIR)){
				SDL_AfficherJoueurTour(pRenderer, posXJoueurTour, posYJoueurTour, radius, taillePolice, COULEUR_BLANC);
			} else {
				SDL_AfficherJoueurTour(pRenderer, posXJoueurTour, posYJoueurTour, radius, taillePolice, COULEUR_NOIR);
			}
			/*On affiche le bouton du menu*/
			SDL_AfficherBoutonMenuPause(pWindow, pRenderer, boutonMenuPause);
			/*On affiche le tout*/
			SDL_RenderPresent(pRenderer);

			SDL_Event e;
			while(SDL_PollEvent(&e)){
				switch(e.type){
					case SDL_QUIT:
						return -1; break;
					case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
								/*Si la fenêtre est redimensionnée, on réaffiche tout l'écran*/
								SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
								SDL_RenderClear(pRenderer);
								SDL_GetWindowSize(pWindow, &window_w, &window_h);
								calculVarPlat(pWindow, &taillePlat, &tailleCase, &posXPlat, &posYPlat, &plateau, &casePlateau);
								radius = tailleCase * 33 / 100;
								posXError = posXPlat;
								posYError = window_h / 60;
								SDL_afficherPlateau(pRenderer, posXPlat, posYPlat, casePlateau, tailleCase);
								SDL_RenderPresent(pRenderer);
							case SDL_WINDOWEVENT_SHOWN:
								/*On affiche la matrice a chaque tour*/
								afficherMatrice(plateauMat, pRenderer, posXPlat, posYPlat, tailleCase, radius);
								SDL_RenderPresent(pRenderer);
								break;
						}
					case SDL_MOUSEBUTTONDOWN:
						posClicX = e.button.x;
						posClicY = e.button.y;
						/*On teste si le click est sur le bouton du menu*/
						if(posClick(e.button, boutonMenuPause.x, boutonMenuPause.y, (boutonMenuPause.x + boutonMenuPause.w), (boutonMenuPause.y + boutonMenuPause.h))){
							quitter = SDL_MenuPause(pWindow, pRenderer);
						} else if(posClick(e.button, posXPlat, posYPlat, (posXPlat + taillePlat), (posYPlat + taillePlat))){
							int caseX;
							int caseY;
							coordCaseClic(posClicX, posClicY, &caseX, &caseY, posXPlat, posYPlat, tailleCase);
							valide = estInvalide(plateauMat, caseY, caseX, joueur, 0);
							if(valide == 0){
								placerPion(plateauMat, caseY, caseX, joueur);
								joueur = strcmp(joueur, NOIR) ? NOIR : BLANC;
							}
						}
						break;
				}
			}
		}

	}

	return 0;
}

int jeuJCIA(SDL_Window * pWindow, SDL_Renderer * pRenderer, int difficulte){
	srand(time(NULL));
	if(pWindow){
		char * couleurs[] = {NOIR, BLANC};
		int chiffreIA = rand() % 2;
		char * couleurIA = couleurs[chiffreIA];

		int window_w, window_h;

		/*Creation des variables du plateau : */
		int taillePlat, tailleCase, posXPlat, posYPlat;
		SDL_Rect plateau;
		SDL_Rect casePlateau;
		int radius;

		/*Creation de la matrice qui contient la disposition des pions*/
		char * plateauMat[TAILLE][TAILLE];
		initTestVide(plateauMat);
		initPlat(plateauMat);

		/*On défini le jouer qui commence*/
		char * joueur = NOIR;

		/*Position du texte d'erreur de coup*/
		int posXError, posYError;
		/*Taille de la police*/
		int taillePolice;
		/*Initialisation du tableau d'erreur*/
		char * coupOk = "";
		char * errorOut = "est en dehors du plateau.";
		char * errorNotEmpty = "n'est pas dans une case vide."; //dans la pratique, il ne sert pas
		char * errorNotNear = "n'est pas a cote d'une case adverse.";
		char * errorDontTake = "ne prend pas de pion adverse.";
		char * cantPlay = "Le joueur n'a pas pu jouer";
		char * error[6] = {coupOk, errorOut, errorNotEmpty, errorNotNear, errorDontTake, cantPlay};

		int posClicX, posClicY;

		int valide = 0;

		int posXJoueurTour, posYJoueurTour;

		/*Creation du bouton du menu*/
		SDL_Rect boutonMenuPause;

		/*Variable de test de quit*/
		int quitter = 0;

		/*compteur de tour pour IA*/
		int nbTour = 1;

		/*On affiche le fond de la fenetre*/
		SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
		SDL_RenderClear(pRenderer);
		SDL_RenderPresent(pRenderer);

		while(!estFinie(plateauMat) && quitter != -2){

			/*On récupère la taille de la fenetre*/
			SDL_GetWindowSize(pWindow, &window_w, &window_h);

			/*Definition des variable du plateau*/
			calculVarPlat(pWindow, &taillePlat, &tailleCase, &posXPlat, &posYPlat, &plateau, &casePlateau);
			/*on calcule la taille d'un pion*/
			radius = tailleCase * 33 / 100;

			posXError = posXPlat;
			posYError = window_h / 60;
			taillePolice = window_w / 53;

			posXJoueurTour = window_w / 60;
			posYJoueurTour = window_h / 60;

			boutonMenuPause.x = window_w / 40;
			boutonMenuPause.y = window_h - window_h / 7;
			boutonMenuPause.w = window_w / 7;
			boutonMenuPause.h = window_h / 10;

			if(!coupPossible(plateauMat, joueur)){
				valide = 5;
				joueur = strcmp(joueur, NOIR) ? NOIR : BLANC;
			}

			SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
			SDL_RenderClear(pRenderer);
			/*On affiche la grille du plateau*/
			SDL_afficherPlateau(pRenderer, posXPlat, posYPlat, casePlateau, tailleCase);
			/*On affiche la matrice du plateau*/
			afficherMatrice(plateauMat, pRenderer, posXPlat, posYPlat, tailleCase, radius);
			/*On affiche l'erreur*/
			SDL_AfficherErreur(pRenderer, error, valide, posXError, posYError, taillePolice);
			/*On affiche le bouton du menu*/
			SDL_AfficherBoutonMenuPause(pWindow, pRenderer, boutonMenuPause);
			/*On affiche le tout*/
			SDL_RenderPresent(pRenderer);

			if(nbTour % 2 == chiffreIA){
				saisieCoupJcIA(plateauMat, joueur, nbTour, difficulte, chiffreIA);
				joueur = strcmp(joueur, NOIR) ? NOIR : BLANC;
				nbTour++;
			}

			SDL_Event e;
			while(SDL_PollEvent(&e)){
				switch(e.type){
					case SDL_QUIT:
						return -1; break;
					case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
								/*Si la fenêtre est redimensionnée, on réaffiche tout l'écran*/
								SDL_SetRenderDrawColor(pRenderer, COULEUR_VERT);
								SDL_RenderClear(pRenderer);
								SDL_GetWindowSize(pWindow, &window_w, &window_h);
								calculVarPlat(pWindow, &taillePlat, &tailleCase, &posXPlat, &posYPlat, &plateau, &casePlateau);
								radius = tailleCase * 33 / 100;
								posXError = posXPlat;
								posYError = window_h / 60;
								SDL_afficherPlateau(pRenderer, posXPlat, posYPlat, casePlateau, tailleCase);
								SDL_RenderPresent(pRenderer);
							case SDL_WINDOWEVENT_SHOWN:
								/*On affiche la matrice a chaque tour*/
								afficherMatrice(plateauMat, pRenderer, posXPlat, posYPlat, tailleCase, radius);
								SDL_RenderPresent(pRenderer);
								break;
						}
					case SDL_MOUSEBUTTONDOWN:
						posClicX = e.button.x;
						posClicY = e.button.y;
						/*On teste si le click est sur le bouton du menu*/
						if(posClick(e.button, boutonMenuPause.x, boutonMenuPause.y, (boutonMenuPause.x + boutonMenuPause.w), (boutonMenuPause.y + boutonMenuPause.h))){
							quitter = SDL_MenuPause(pWindow, pRenderer);
						} else if(posClick(e.button, posXPlat, posYPlat, (posXPlat + taillePlat), (posYPlat + taillePlat))){
							int caseX;
							int caseY;
							coordCaseClic(posClicX, posClicY, &caseX, &caseY, posXPlat, posYPlat, tailleCase);
							valide = estInvalide(plateauMat, caseY, caseX, joueur, 0);
							if(valide == 0){
								placerPion(plateauMat, caseY, caseX, joueur);
								joueur = strcmp(joueur, NOIR) ? NOIR : BLANC;
								nbTour++;
							}
						}
						break;
				}
			}
		}

	}

	return 0;
}
