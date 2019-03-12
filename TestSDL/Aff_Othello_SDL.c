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
#include "SDL_Othello.h"

int main(int argc, char** argv){
	//Ouvrir la fenêtre et mémoriser son pointeur
	SDL_Window* pWindow = NULL;
	pWindow = showWindow();
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	// Le pointeur vers notre police

	/*Variables contenant la position d'un clic*/
	int posClicX, posClicY;

	/*Variables contenant la taille de la fenetre*/
	int window_w, window_h;

	char * plateauMat[TAILLE][TAILLE];
	initTestVide(plateauMat);
	//initTestRand(plateauMat);
	initPlat(plateauMat);
	//afficherPlateau(plateauMat);

	/*On défini le jouer qui commence*/
	char * joueur = NOIR;

	/*Creation des variables du plateau : */
	int taillePlat, tailleCase, posXPlat, posYPlat;
	SDL_Rect plateau;
	SDL_Rect plateau_case;
	int radius;
	SDL_Rect bouton_quit;

	/*Position du texte d'erreur de coup*/
	int posXError, posYError;
	/*Taille de la police*/
	int taillePolice;
	/*Initialisation du tableau d'erreur*/
	char * coupOk = "";
	char * errorOut = "est en dehors du plateau.";
	char * errorNotEmpty = "Le coup est n'est pas dans une case vide.";
	char * errorDontTake = "Le coup ne prend pas de pion adverse.";
	char * error[4] = {coupOk, errorOut, errorNotEmpty, errorDontTake};


	if(pWindow){
		/*On affiche le fond de la fenetre*/
		SDL_SetRenderDrawColor(renderer, COULEUR_VERT);
		SDL_RenderClear(renderer);
		/*Pas besoin de le recharger lorsque l'on réaffiche le plateau*/
		int running = 1;
		while(running){
			SDL_Delay(1);
			/*On récupère la taille de la fenetre*/
			SDL_GetWindowSize(pWindow, &window_w, &window_h);

			/*Définition des variables du plateau*/
			calculVarPlat(pWindow, &taillePlat, &tailleCase, &posXPlat, &posYPlat, &plateau, &plateau_case);
			/*on calcule la taille d'un pion*/
			radius = tailleCase * 33 / 100;

			posXError = posXPlat;
			posYError = 10;
			taillePolice = window_w / 53;

			/*On affiche la grille du plateau*/
			SDL_afficherPlateau(renderer, posXPlat, posYPlat, plateau_case, tailleCase);
			/*On affiche la matrice du plateau*/
			afficherMatrice(plateauMat, renderer, posXPlat, posYPlat, tailleCase, radius);

			/*On calcule les dimensions du bouton pour quitter*/
			bouton_quit.w = bouton_quit.h = window_w * 2 / 100;
			bouton_quit.x = window_w - bouton_quit.w;
			bouton_quit.y = 0;
			/*On affiche le bouton*/
			SDL_SetRenderDrawColor(renderer, COULEUR_ROUGE);
			SDL_RenderFillRect(renderer, &bouton_quit);
			/*On affiche le tout*/
			SDL_RenderPresent(renderer);


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
								/*Si la fenêtre est redimensionnée, on réaffiche tout l'écran*/
								SDL_SetRenderDrawColor(renderer, COULEUR_VERT);
								SDL_RenderClear(renderer);
								SDL_GetWindowSize(pWindow, &window_w, &window_h);
								calculVarPlat(pWindow, &taillePlat, &tailleCase, &posXPlat, &posYPlat, &plateau, &plateau_case);
								radius = tailleCase * 33 / 100;
								posXError = posXPlat;
								SDL_afficherPlateau(renderer, posXPlat, posYPlat, plateau_case, tailleCase);
								bouton_quit.w = bouton_quit.h = window_w * 2 / 100;
								bouton_quit.x = window_w - bouton_quit.w;
								SDL_SetRenderDrawColor(renderer, COULEUR_ROUGE);
								SDL_RenderFillRect(renderer, &bouton_quit);
								SDL_RenderPresent(renderer);
							case SDL_WINDOWEVENT_SHOWN:

								/*On affiche la matrice a chaque tour*/
								afficherMatrice(plateauMat, renderer, posXPlat, posYPlat, tailleCase, radius);

								/*IMAGE
								si on met du texte sur des image il faut juste mettre les images avant
								drawImage(renderer, 500, 150, "Umaru.png");
								drawImage(renderer, 500, 300, "Umaru.png");
								drawImage(renderer, 500, 450, "Umaru.png");

								drawText(renderer, 525, 175, "Texte");
								drawText(renderer, 525, 325, "Texte");
								drawText(renderer, 525, 475, "Texte");
								*/
								/*RECTANGLE
								SDL_Rect rect;
								rect.x = 50;
								rect.y = 50;
								rect.w = 50;
								rect.h = 50;
								SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
								SDL_RenderFillRect(renderer, &rect);
								*/
								/*REMPLIR LE TABLEAU
								int n1, n2;
								for(n1 = 0; n1 < 8; n1++){
								for(n2 = 0; n2 < 8; n2++){
								int posXCircle, posYCircle;
								posXCircle = posXPlat + (tailleCase / 2);	//on crée les positions X et Y a partir du radius,
								posYCircle = posYPlat + (tailleCase / 2);	//(en haut a gauche)
								afficherPion(renderer, posXCircle, posYCircle, radius, HEXA_NOIR);
								posXCircle = posXCircle + tailleCase;
								}
								posXCircle = posXPlat + (tailleCase / 2);
								posYCircle = posYCircle + tailleCase;
								*/

								SDL_RenderPresent(renderer);
								break;
						}
						break;
					case SDL_MOUSEBUTTONDOWN:
						/*Lorsque l'on clique, on efface les erreurs de coup*/
						/*Si le coup est valide, suppression des erreurs précedentes*/
						SDL_SetRenderDrawColor(renderer, COULEUR_VERT);
						SDL_Rect errorClean = {posXError, posYError, taillePlat, posYError + (taillePolice * 2)};
						SDL_RenderFillRect(renderer, &errorClean);
						SDL_RenderPresent(renderer);

						posClicX = e.button.x;
						posClicY = e.button.y;
						int x, y;
						SDL_GetWindowSize(pWindow, &x, &y);
						if(posClick(e.button, bouton_quit.x, bouton_quit.y,  bouton_quit.x + bouton_quit.w, bouton_quit.y + bouton_quit.h)){
							SDL_DestroyWindow(pWindow);
							SDL_DestroyRenderer(renderer);
							TTF_Quit();
							SDL_Quit();
							return 0;
						} else if(posClick(e.button, posXPlat, posYPlat, (posXPlat + taillePlat), (posYPlat + taillePlat))){
							int caseX;
							int caseY;
							coordCaseClic(posClicX, posClicY, &caseX, &caseY, posXPlat, posYPlat, tailleCase);
							/*
							printf("DANS LE PLATEAU\n");
							printf("%d : %d\n", posClicX, posClicY);
							printf("%d : %c\n", caseX + 1, caseY + 'A');
							printf("%d\n", tailleCase);
							*/
							int valide = estInvalide(plateauMat, caseY, caseX, joueur);
							if(valide == 0){
								placerPion(plateauMat, caseY, caseX, joueur);
								joueur = strcmp(joueur, NOIR) ? NOIR : BLANC;
							} else {
								drawText(renderer, posXError, posYError, "Le coup que vous avez voulu jouer", taillePolice, COULEUR_NOIR);
								drawText(renderer, posXError, posYError + taillePolice + 5, error[valide], taillePolice, COULEUR_NOIR);
							}
						}
						break;
				}
			}
		}
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);
	//Destruction du renderer
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
    SDL_Quit();

    return 0;
}
