all: project

project: tail.o 
	gcc tail.o -o project

tail.o: tail.c functions.h
	gcc -c tail.c

clean:
	rm -rf *o project
