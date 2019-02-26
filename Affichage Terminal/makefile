out : main.o testaff.o
	gcc main.o testaff.o -o out
main.o : main.c
	gcc main.c -c
testaff.o : testaff.c
	gcc testaff.c -c

clean:
	rm *.o
