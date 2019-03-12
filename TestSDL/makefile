CC=gcc
FLAGS=-Wall -g
MOREFLAGS=-Wno-unused-variable -Wno-unused-but-set-variable
SDL_DIR=/mnt/c/Bash/SDL2
#$HOME/SDL2 pour linux; $HOME/SDLMAC pour mac; /mnt/c/Bash/SDL2 pour PC perso (pour Nathan)
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -L/usr/lib/x86_64-linux-gnu/ -lSDL2_ttf -lm
INCS=-I${SDL_INC_DIR}
PROG=othelloSDL
DEPENDANCE=init.o aff.o SDL_Othello.o tour.o

all: sdl_text
delete: clean phony

sdl_text: Aff_Othello_SDL.o ${DEPENDANCE}
	${CC} Aff_Othello_SDL.o ${DEPENDANCE} -o ${PROG} ${LIBS} ${INCS} ${FLAGS}

Aff_Othello_SDL.o: Aff_Othello_SDL.c
	${CC} Aff_Othello_SDL.c -c ${LIBS} ${INCS} ${FLAGS} ${MOREFLAGS}

init.o: ../Init/init.c
	${CC} ../Init/init.c -c

aff.o: ../Aff/aff.c
	${CC} ../Aff/aff.c -c

tour.o: ../Tour/tour.c
	${CC} ../Tour/tour.c -c

SDL_Othello.o : SDL_Othello.c
	${CC} SDL_Othello.c -c ${LIBS} ${INCS}

test: testSDL.c
	gcc -c `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf testSDL.c

test2: testSDL.o
	gcc -o sdl_test testSDL.o `sdl-config --libs` -lSDL_ttf

clear:
	clear ; clear

clean:
	rm -f *.o

phony:
	rm -f ${PROG}

#Explications :
#. -L : permet de spécifier où trouver la bibliothèque libSDL2.so
#. -l : permet de dire qu’il faut utiliser la bibliothèque SDL2
#. -I : permet de spécificer où sont les fichiers .h
