out : main.o aff.o init.o
	gcc main.o aff.o init.o -o out
main.o : main.c
	gcc main.c -c
aff.o : aff.c
	gcc aff.c -c
init.o : init.c
	gcc init.c -c


clean:
	rm *.o
