CC=gcc
FLAGS=-Wall -g
MOREFLAGS=-Wno-unused-variable
SDL_DIR=${HOME}/SDLMAC
#SDL2 pour linux SDLMAC pour mac (pour Nathan)
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=sdl_test
DEPENDANCE=init.o

all: sdl_text

sdl_text: testSDL.o ${DEPENDANCE}
	${CC} testSDL.o ${DEPENDANCE} -o ${PROG} ${LIBS} ${INCS} ${FLAGS} ${MOREFLAGS}

testSDL.o: testSDL.c
	${CC} testSDL.c -c ${LIBS} ${INCS} ${FLAGS} ${MOREFLAGS}

init.o: ../Init/init.c
	${CC} ../Init/init.c -c


clear:
	clear ; clear

clean:
	rm -f ${PROG}
	rm -f *.o

#Explications :
#. -L : permet de spécifier où trouver la bibliothèque libSDL2.so
#. -l : permet de dire qu’il faut utiliser la bibliothèque SDL2
#. -I : permet de spécificer où sont les fichiers .h
