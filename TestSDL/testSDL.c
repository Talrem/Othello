#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


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
	return SDL_CreateWindow("AAAAA",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													1680,
													1050,
													SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
}

/*Renvoie 1 si le click est dans les coordonées rentrées. 0 sinon*/
int posClick(SDL_MouseButtonEvent b, int posA_x, int posA_y, int posB_x, int posB_y){
   int x = b.x;
   int y = b.y;
   int in = 0;
   if((x > posA_x && y > posA_y) && (x < posB_x && y < posB_y))
      in++;
   return in;
}

int main(int argc, char** argv)
{
	//Ouvrir la fenêtre et mémoriser son pointeur
	SDL_Window* pWindow = NULL;
   pWindow = showWindow();
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Renderer *renderer= NULL;
   renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	// Le pointeur vers notre police

   int x, y;




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

								drawImage(renderer, 500, 150, "Umaru.png");
								drawImage(renderer, 500, 300, "Umaru.png");
								drawImage(renderer, 500, 450, "Umaru.png");

								drawText(renderer, 525, 175, "Texte");
								drawText(renderer, 525, 325, "Texte");
								drawText(renderer, 525, 475, "Texte");


                        /* On fait le rendu ! */
                        SDL_Rect rect;
                        rect.x = 50;
                        rect.y = 50;
                        rect.w = 50;
                        rect.h = 50;
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        SDL_RenderFillRect(renderer, &rect);
                        SDL_RenderPresent(renderer);
							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:
                  x = e.button.x;
                  y = e.button.y;
                  if(posClick(e.button, 50, 50, 100, 100)){
                     drawText(renderer, 60, 60, "GG");
                     SDL_RenderPresent(renderer);
                  }

						/*drawText(renderer, 50, 50, "Je détecte les clicks, sa mère");
						SDL_RenderPresent(renderer);*/
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
