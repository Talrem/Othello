#define TAILLE 8
#define VIDE " "


#if defined(WIN32)
  #define NOIR "@"
  #define BLANC "O"
#elif defined (linux)
  #define NOIR "●"
  #define BLANC "○"
#endif
