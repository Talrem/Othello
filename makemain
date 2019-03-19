all: out clean
	
out: main.o aff.o init.o tour.o
	gcc main.o aff.o init.o tour.o -o Othello.exe
main.o: main.c
	gcc main.c -c
aff.o: ./Aff/aff.c
	gcc ./Aff/aff.c -c
init.o: ./Init/init.c
	gcc ./Init/init.c -c
tour.o: ./Tour/tour.c
	gcc ./Tour/tour.c -c

clean:
	rm *.o
