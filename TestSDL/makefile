CC=gcc
FLAGS=-Wall -g
MOREFLAGS=-Wno-unused-variable -Wno-unused-but-set-variable
SDL_DIR=/mnt/c/Bash/SDL2
#SDL2 pour linux SDLMAC pour mac (pour Nathan)
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -L/usr/lib/x86_64-linux-gnu/ -lSDL2_ttf -lm
INCS=-I${SDL_INC_DIR}
PROG=sdl_test
DEPENDANCE=init.o aff.o

all: sdl_text

sdl_text: testSDL.o ${DEPENDANCE}
	${CC} testSDL.o ${DEPENDANCE} -o ${PROG} ${LIBS} ${INCS} ${FLAGS} ${MOREFLAGS}

testSDL.o: testSDL.c
	${CC} testSDL.c -c ${LIBS} ${INCS} ${FLAGS} ${MOREFLAGS}

init.o: ../Init/init.c
	${CC} ../Init/init.c -c

aff.o: ../Aff/aff.c
	${CC} ../Aff/aff.c -c

test: testSDL.c
	gcc -c `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf testSDL.c

test2: testSDL.o
	gcc -o sdl_test testSDL.o `sdl-config --libs` -lSDL_ttf

clear:
	clear ; clear

clean:
	rm -f ${PROG}
	rm -f *.o

#Explications :
#. -L : permet de spécifier où trouver la bibliothèque libSDL2.so
#. -l : permet de dire qu’il faut utiliser la bibliothèque SDL2
#. -I : permet de spécificer où sont les fichiers .h
