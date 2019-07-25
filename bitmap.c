#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "bitmap.h"

pixel_t *bitmap;
uint16_t *depth_buffer;

void alloc_bitmap()
{
	bitmap = calloc(BITMAP_SIZE, 1);
	depth_buffer = calloc(BITMAP_SIZE, 1);
	memset(depth_buffer, 255, BITMAP_SIZE);
}

void write_bmp()
{
	char str[12];
	static int frame = 0;
	sprintf(str, "pic%04d.bmp", frame++);

	FILE *f = fopen(str, "wb");
	fwrite(&header, sizeof(header), 1, f);
	fwrite(bitmap, sizeof(pixel_t), BITMAP_SIZE, f);

	// refresh buffers
	memset(bitmap, 0, BITMAP_SIZE);
	memset(depth_buffer, 255, BITMAP_SIZE);

	fclose(f);
}

void free_bitmap()
{
	free(bitmap);
	free(depth_buffer);
}
