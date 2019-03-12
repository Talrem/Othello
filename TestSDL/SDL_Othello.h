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
#define COULEUR_NOIR 0, 0, 0, 0
#define COULEUR_ROUGE 255, 0, 0, 255
#define POLICE "BEBAS.ttf"

void drawText (SDL_Renderer * renderer, int x, int y, char * string, int policeSize, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
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
