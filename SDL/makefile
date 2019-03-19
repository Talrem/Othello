CC=gcc
FLAGS=-Wall -g
MOREFLAGS=-Wno-unused-variable -Wno-unused-but-set-variable
SDL_DIR=${HOME}/SDL2
#${HOME}/SDL2 pour linux; ${HOME}/SDLMAC pour mac; /mnt/c/Bash/SDL2 pour PC perso (pour Nathan)
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -L/usr/lib/x86_64-linux-gnu/ -lSDL2_ttf -lm
INCS=-I${SDL_INC_DIR}
PROG=othelloSDL
DEPENDANCE=init.o aff.o SDL_Othello.o tour.o

all: sdl clean
delete: clean phony

sdl: SDL.o ${DEPENDANCE}
	${CC} SDL.o ${DEPENDANCE} -o ${PROG} ${LIBS} ${INCS} ${FLAGS}

SDL.o: SDL.c
	${CC} SDL.c -c ${LIBS} ${INCS} ${FLAGS}

init.o: ../Init/init.c
	${CC} ../Init/init.c -c

aff.o: ../Aff/aff.c
	${CC} ../Aff/aff.c -c

tour.o: ../Tour/tour.c
	${CC} ../Tour/tour.c -c

SDL_Othello.o : ../TestSDL/SDL_Othello.c
	${CC} ../TestSDL/SDL_Othello.c -c ${LIBS} ${INCS}

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
