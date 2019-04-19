#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define TAILLE 8
#define MAX_C 20
#define VIDE " "

#if defined(WIN32)
  #define NOIR "@"
  #define BLANC "O"
#elif defined (linux)
  #define NOIR "●"
  #define BLANC "○"
#endif
