run: main.o draw.o
	gcc -o run main.o draw.o -lpng

main.o: main.c image.h
	gcc -g -c main.c

draw.o: draw.c image.h
	gcc -g -c draw.c
