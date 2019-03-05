#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


void drawText (SDL_Renderer * renderer, int x, int y, char * string){
	TTF_Font *police = TTF_OpenFont("ChowFun.ttf", 20);
	SDL_Color couleurDoree = {204, 154, 0};
	SDL_Surface *texte = TTF_RenderUTF8_Blended(police, string, couleurDoree);

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
	SDL_Surface*image=IMG_LoadPNG_RW(rwop);
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
	return SDL_CreateWindow("Final Fantasy: the great shity C project",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													1680,
													1050,
													SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
}

int main(int argc, char** argv)
{
	//Ouvrir la fenêtre et mémoriser son pointeur
	SDL_Window* pWindow = showWindow();
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Renderer *renderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	// Le pointeur vers notre police






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
								/* Le fond de la fenêtre sera blanc */
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderClear(renderer);
								//si on met du texte sur des image il faut juste mettre les images avant

								drawImage(renderer, 500, 150, "button.png");
								drawImage(renderer, 500, 300, "button.png");
								drawImage(renderer, 500, 450, "button.png");

								drawText(renderer, 525, 175, "Nouvelle partie");
								drawText(renderer, 525, 325, "Charger une partie");
								drawText(renderer, 525, 475, "Quitter le meilleur jeu du monde");


                /* On fait le rendu ! */
                SDL_RenderPresent(renderer);
							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:

						drawText(renderer, 50, 50, "Je détecte les clicks, sa mère");
						SDL_RenderPresent(renderer);
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