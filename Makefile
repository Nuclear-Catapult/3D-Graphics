run: draw.o triangle.o line.o bitmap.o vertice.o transformations.o
	gcc draw.o triangle.o line.o bitmap.o vertice.o transformations.o -o run -lm
	-@echo "Compilation complete. Run 'make video' to generate video.mp4"

draw.o: draw.c transformations.h triangle.h bitmap.h
	gcc -g -c draw.c

transformations.o: transformations.c transformations.h
	gcc -g -c transformations.c

triangle.o: triangle.c triangle.h line.h
	gcc -g -c triangle.c

vertice.o: vertice.c vertice.h
	gcc -g -c vertice.c

line.o: line.c line.h bitmap.h triangle.h
	gcc -g -c line.c

bitmap.o: bitmap.c bitmap.h vertice.h
	gcc -g -c bitmap.c

clean:
	rm *.o

video:
	./run
	rm -f video.mp4 2> /dev/null
	ffmpeg -r 30 -f image2 -s 500x500 -i pic%04d.bmp -vcodec libx264 -crf 15 -pix_fmt yuv420p video.mp4
	rm *.bmp
