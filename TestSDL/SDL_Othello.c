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

void drawText (SDL_Renderer * renderer, int x, int y, char * string, int policeSize, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	TTF_Font *police = TTF_OpenFont(POLICE, policeSize);
	SDL_Color couleur = {r, g, b};
	SDL_Surface *texte = TTF_RenderUTF8_Blended(police, string, couleur);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
	/* Position ou sera mis le texte dans la fenêtre */
	SDL_Rect txtDestRect;
	txtDestRect.x = x;
	txtDestRect.y = y;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
}

void drawImage (SDL_Renderer * renderer, int x, int y, char * string){
	// x et y les coordonnées,
	SDL_RWops *rwop=SDL_RWFromFile(string, "rb");
	SDL_Rect imgDestRect;
	imgDestRect.x = x;
	imgDestRect.y = y;
	SDL_Surface *image=IMG_LoadPNG_RW(rwop);
	SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */
	SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
	SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);
}

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

int posClick(SDL_MouseButtonEvent b, int posA_x, int posA_y, int posB_x, int posB_y){
   int x = b.x;
   int y = b.y;
   int in = 0;
   if((x > posA_x && y > posA_y) && (x < posB_x && y < posB_y))
      in++;
   return in;
}

/*https://gist.github.com/derofim/912cfc9161269336f722*/
void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	SDL_SetRenderDrawColor(rend, r,g,b,a);
	SDL_RenderDrawPoint(rend, x, y);
}
void draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	// if the first pixel in the screen is represented by (0,0) (which is in sdl)
	// remember that the beginning of the circle is not in the middle of the pixel
	// but to the left-top from it:

	double error = (double)-radius;
	double x = (double)radius - 0.5;
	double y = (double)0.5;
	double cx = n_cx - 0.5;
	double cy = n_cy - 0.5;

	while (x >= y){
		set_pixel(surface, (int)(cx + x), (int)(cy + y), r, g, b, a);
		set_pixel(surface, (int)(cx + y), (int)(cy + x), r, g, b, a);

		if (x != 0){
			set_pixel(surface, (int)(cx - x), (int)(cy + y), r, g, b, a);
			set_pixel(surface, (int)(cx + y), (int)(cy - x), r, g, b, a);
		}

		if (y != 0){
			set_pixel(surface, (int)(cx + x), (int)(cy - y), r, g, b, a);
			set_pixel(surface, (int)(cx - y), (int)(cy + x), r, g, b, a);
		}

		if (x != 0 && y != 0){
			set_pixel(surface, (int)(cx - x), (int)(cy - y), r, g, b, a);
			set_pixel(surface, (int)(cx - y), (int)(cy - x), r, g, b, a);
		}

		error += y;
		++y;
		error += y;

		if (error >= 0){
			--x;
			error -= x;
			error -= x;
		}
	}
}
void fill_circle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	// Note that there is more to altering the bitrate of this
	// method than just changing this value.  See how pixels are
	// altered at the following web page for tips:
	//   http://www.libsdl.org/intro.en/usingvideo.html
	//static const int BPP = 4;
	SDL_Renderer *gRenderer = surface;
	//double ra = (double)radius;

	for (double dy = 1; dy <= radius; dy += 1.0){
		// This loop is unrolled a bit, only iterating through half of the
		// height of the circle.  The result is used to draw a scan line and
		// its mirror image below it.

		// The following formula has been simplified from our original.  We
		// are using half of the width of the circle because we are provided
		// with a center and we need left/right coordinates.

		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		//int x = cx - dx;
		SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
		SDL_RenderDrawLine(gRenderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(gRenderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);

		// Grab a pointer to the left-most pixel for each half of the circle
		/*Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
		Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
		for (; x <= cx + dx; x++)
		{
			*(Uint32 *)target_pixel_a = pixel;
			*(Uint32 *)target_pixel_b = pixel;
			target_pixel_a += BPP;
			target_pixel_b += BPP;
		}*/
		/*
		// sleep for debug
		SDL_RenderPresent(gRenderer);
		std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
		*/
	}
}

void calculVarPlat(SDL_Window *pWindow, int *taillePlat, int *tailleCase, int *posXPlat, int *posYPlat, SDL_Rect *plateau, SDL_Rect *plateau_case){
	int window_w, window_h;
	SDL_GetWindowSize(pWindow, &window_w, &window_h);
	if(window_w >= window_h){
		*taillePlat = window_h * 80 / 100;
		*posXPlat = (window_w - *taillePlat) / 2;
		*posYPlat = (window_h - *taillePlat) / 2;
	} else {
		*taillePlat = window_w * 80 / 100;
		*posXPlat = (window_w - *taillePlat) / 2;
		*posYPlat = (window_h - *taillePlat) / 2;
	}
	*tailleCase = *taillePlat / 8;
	plateau->x = *posXPlat;
	plateau->y = *posYPlat;
	plateau->w = *taillePlat;
	plateau->h = *taillePlat;
	plateau_case->x = *posXPlat;
	plateau_case->y = *posYPlat;
	plateau_case->w = *tailleCase;
	plateau_case->h = *tailleCase;
}

void SDL_afficherPlateau(SDL_Renderer *renderer, int posXPlat, int posYPlat, SDL_Rect plateau_case, int tailleCase){
	SDL_SetRenderDrawColor(renderer, HEXA_POURPRE);
	int i, j;
	for(i = 0; i <= 8; i++){
		for(j = 0; j <= 8; j++){
			SDL_RenderDrawRect(renderer, &plateau_case);
			plateau_case.x = posXPlat + j * tailleCase;
		}
		plateau_case.x = posXPlat;
		plateau_case.y = posYPlat + i * tailleCase;
	}
	plateau_case.x = posXPlat;
	plateau_case.y = posYPlat;
	SDL_Rect rect = {posXPlat-1, posYPlat-1, tailleCase * 8, tailleCase * 8};
	SDL_RenderDrawRect(renderer, &rect);
}

void afficherPion(SDL_Renderer *renderer, int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	fill_circle(renderer, x, y, radius, r, g, b, a);
};

void afficherMatrice(char * plateau[TAILLE][TAILLE], SDL_Renderer *render, int posXPlat, int posYPlat, int tailleCase, int radius){
	int i, j;
	int posXpion, posYpion;
	for(i = 0; i < TAILLE; i++){
		for(j = 0; j < TAILLE; j++){
			if(!strcmp(plateau[i][j], NOIR)){
				posXpion = posXPlat + (tailleCase * (j + 1)) - tailleCase / 2;
				posYpion = posYPlat + (tailleCase * (i + 1)) - tailleCase / 2;
				afficherPion(render, posXpion, posYpion, radius, HEXA_NOIR);
			} else if(!strcmp(plateau[i][j], BLANC)){
				posXpion = posXPlat + (tailleCase * (j + 1)) - tailleCase / 2;
				posYpion = posYPlat + (tailleCase * (i + 1)) - tailleCase / 2;
				afficherPion(render, posXpion, posYpion, radius, HEXA_BLANC);
			}
		}
	}
};

void placerPion(char *plateau[TAILLE][TAILLE], int x, int y, char * joueur){
    plateau[x][y] = joueur;
}

void coordCaseClic(int clicX, int clicY, int *caseX, int *caseY, int posXPlat, int posYPlat, int tailleCase){
    *caseX = clicX - posXPlat;
    *caseY = clicY - posYPlat;
    *caseX = (*caseX / tailleCase);
    *caseY = (*caseY / tailleCase);
}
