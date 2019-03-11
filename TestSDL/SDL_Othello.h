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
#define HEXA_POURPRE 0x93, 0x00, 0x18, 0xFF
#define HEXA_NOIR 0x00, 0x00, 0x00, 0xFF
#define HEXA_BLANC 0xFF, 0xFF, 0xFF, 0xFF
#define COULEUR_VERT 0, 177, 106, 1

#define LOAD_PLAT SDL_SetRenderDrawColor(renderer, COULEUR_VERT); SDL_RenderClear(renderer); calculVarPlat(pWindow, &taillePlat, &tailleCase, &posXPlat, &posYPlat, &plateau, &plateau_case); radius = tailleCase * 33 / 100; SDL_SetRenderDrawColor(renderer, HEXA_NOIR); SDL_afficherPlateau(renderer, posXPlat, posYPlat, plateau_case, tailleCase); afficherMatrice(plateauMat, renderer, posXPlat, posYPlat, tailleCase, radius); bouton_quit.w = bouton_quit.h = window_w * 3 / 100; SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); SDL_RenderFillRect(renderer, &bouton_quit); SDL_RenderPresent(renderer);
/*Permet de Load le plateau, dynamiquement par rapport
a la taille de la fenetre
Affiche le fond en vert,
Calcul de la taille du plateau, sa position
la taille d'une case et le rayon des pions*/

void drawText (SDL_Renderer * renderer, int x, int y, char * string, int policeSize);
void drawImage (SDL_Renderer * renderer, int x, int y, char * string);
SDL_Window* showWindow();
int posClick(SDL_MouseButtonEvent b, int posA_x, int posA_y, int posB_x, int posB_y);
void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void fill_circle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void calculVarPlat(SDL_Window *pWindow, int *taillePlat, int *tailleCase, int *posXPlat, int *posYPlat, SDL_Rect *plateau, SDL_Rect *plateau_case);
void SDL_afficherPlateau(SDL_Renderer *renderer, int posXPlat, int posYPlat, SDL_Rect plateau_case, int tailleCase);
void afficherPion(SDL_Renderer *renderer, int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void afficherMatrice(char * plateau[TAILLE][TAILLE], SDL_Renderer *render, int posXPlat, int posYPlat, int tailleCase, int radius);
void placerPion(char *plateau[TAILLE][TAILLE], int x, int y, char * joueur);
void coordCaseClic(int clicX, int clicY, int *caseX, int *caseY, int posXPlat, int posYPlat, int tailleCase);
