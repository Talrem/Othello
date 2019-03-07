#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../Init/init.h"
#include "../definitions.h"
#define HEXA_POURPRE 0x93, 0x00, 0x18, 0xFF
#define HEXA_NOIR 0x00, 0x00, 0x00, 0xFF
#define HEXA_BLANC 0xFF, 0xFF, 0xFF, 0xFF
#define COULEUR_VERT 0, 177, 106, 1


void drawText (SDL_Renderer * renderer, int x, int y, char * string){
	TTF_Font *police = TTF_OpenFont("Minecraft.ttf", 20);
	SDL_Color couleur = {0, 0, 0};
	SDL_Surface *texte = TTF_RenderUTF8_Blended(police, string, couleur);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

	/* Initialisation simple */
	SDL_Init(SDL_INIT_VIDEO);
	/* Initialisation TTF */
	TTF_Init();
	/* Création de la fenêtre */
	return SDL_CreateWindow("Othello",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													1680,
													1050,
													SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
}

/*Renvoie 1 si le clic est dans les coordonées rentrées. 0 sinon*/
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

void calculVarPlat(SDL_Window *pWindow, int *taillePlat, int *tailleCase, int *posXPlat, int *posYPlat){
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
}

void afficherPlateau(SDL_Renderer *renderer, int posXPlat, int posYPlat, SDL_Rect plateau_case, int tailleCase){
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

void afficherMatrice(char * plateau[TAILLE][TAILLE], SDL_Renderer *render, int posXPlat, int posYPlat, ){

};

int main(int argc, char** argv)
{
	//Ouvrir la fenêtre et mémoriser son pointeur
	SDL_Window* pWindow = NULL;
   pWindow = showWindow();
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Renderer *renderer= NULL;
   renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	// Le pointeur vers notre police

	/*Variables contenant la position d'un clic*/
   int posClicX, posClicY;

	/*Variables contenant la taille de la fenetre*/
	int window_w, window_h;

	char * plateauMat[TAILLE][TAILLE];
	initTestRand(plateauMat);


	if( pWindow )
	{
		int running = 1;
		while(running) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: running = 0;
					break;
					case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:

								/*Si la fenetre est redimensionnée, on récupère la nouvelle taille*/
								SDL_GetWindowSize(pWindow, &window_w, &window_h);

								/* Le fond de la fenêtre sera
								vert : rgba(0, 177, 106, 1) */
                        SDL_SetRenderDrawColor(renderer, COULEUR_VERT);
								SDL_RenderClear(renderer);

								/*{IMAGE
								si on met du texte sur des image il faut juste mettre les images avant
								drawImage(renderer, 500, 150, "Umaru.png");
								drawImage(renderer, 500, 300, "Umaru.png");
								drawImage(renderer, 500, 450, "Umaru.png");

								drawText(renderer, 525, 175, "Texte");
								drawText(renderer, 525, 325, "Texte");
								drawText(renderer, 525, 475, "Texte");
								}*/

                        /*{RECTANGLE
								SDL_Rect rect;
                        rect.x = 50;
                        rect.y = 50;
                        rect.w = 50;
                        rect.h = 50;
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        SDL_RenderFillRect(renderer, &rect);
								}*/

								/*Définition de la taille du plateau*/
								int taillePlat, tailleCase, posXPlat, posYPlat;
								calculVarPlat(pWindow, &taillePlat, &tailleCase, &posXPlat, &posYPlat);

								SDL_Rect plateau = {posXPlat, posYPlat, taillePlat, taillePlat};
								SDL_Rect plateau_case = {posXPlat, posYPlat, tailleCase, tailleCase};
								SDL_SetRenderDrawColor(renderer, HEXA_NOIR);
								afficherPlateau(renderer, posXPlat, posYPlat, plateau_case, tailleCase);

								int radius, posXCircle, posYCircle;
								radius = tailleCase * 33 / 100;
								posXCircle = posXPlat + (tailleCase / 2);	//on crée les positions X et Y a partir du radius,
								posYCircle = posYPlat + (tailleCase / 2);	//(en haut a gauche)

								//REMPLIR LE TABLEAU
								int n1, n2;
								for(n1 = 0; n1 < 8; n1++){
									for(n2 = 0; n2 < 8; n2++){
										afficherPion(renderer, posXCircle, posYCircle, radius, HEXA_NOIR);
										posXCircle = posXCircle + tailleCase;
									}
									posXCircle = posXPlat + (tailleCase / 2);
									posYCircle = posYCircle + tailleCase;
								}

                        SDL_RenderPresent(renderer);
							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:
                  posClicX = e.button.x;
                  posClicY = e.button.y;
                  if(posClick(e.button, 50, 50, 100, 100)){
                     drawText(renderer, 60, 60, "GG");
                     SDL_RenderPresent(renderer);
                  }
					break;
				}
			}
		}
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);


	TTF_Quit();
    SDL_Quit();

    return 0;
}
