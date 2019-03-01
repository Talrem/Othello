CC=gcc
FLAGS=-Wall -g -Wno-unused-variable
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=sdl_test

all: sdl_text

sdl_text: sdl_test.c
	${CC} sdl_test.c -o ${PROG} ${LIBS} ${INCS} ${FLAGS}

clear:
	clear ; clear

clean:
	rm -f ${PROG}
	rm -f *.o

#Explications :
#. -L : permet de spécifier où trouver la bibliothèque libSDL2.so
#. -l : permet de dire qu’il faut utiliser la bibliothèque SDL2
#. -I : permet de spécificer où sont les fichiers .h
