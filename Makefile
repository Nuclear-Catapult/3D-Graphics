run: draw.o triangle.o line.o bitmap.o vertice.o
	gcc draw.o triangle.o line.o bitmap.o vertice.o -o run
	-@echo "Compilation complete. Run ./render.sh to generate video.mp4"

draw.o: draw.c triangle.h bitmap.h
	gcc -g -c draw.c

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
