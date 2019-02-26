out : main.o aff.o init.o
	gcc main.o aff.o init.o -o out
main.o : main.c
	gcc main.c -c
aff.o : ./Aff/aff.c
	gcc ./Aff/aff.c -c
init.o : ./Init/init.c
	gcc ./Init/init.c -c


clean:
	rm *.o
