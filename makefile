all : forkin.o
	gcc forkin.o

forkin.o : forkin.c
	gcc -c forkin.c

run :
	./a.out

clean : 
	rm *.o a.out
