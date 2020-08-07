run: draw.o triangle.o line.o bitmap.o vertice.o transformations.o
	gcc draw.o triangle.o line.o bitmap.o vertice.o transformations.o -o run -lm
	-@echo "Compilation complete. Run ./render.sh to generate video.mp4"

draw.o: draw.c transformations.h triangle.h bitmap.h
	gcc -g -c draw.c

transformations.o: transformations.c transformations.h
	gcc -g -c transformations.c

triangle.o: triangle.c triangle.h line.h
	gcc -g -c triangle.c

vertice.o: vertice.c vertice.h
	gcc -g -c vertice.c

line.o: line.c line.h bitmap.h
	gcc -g -c line.c

bitmap.o: bitmap.c bitmap.h vertice.h
	gcc -g -c bitmap.c

clean:
	rm *.o
