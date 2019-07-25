#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "bitmap.h"

#pragma pack(1)
struct header_t {
	const uint16_t BM;
	const uint32_t total_size;
	const uint32_t reserved;
	const uint32_t offset;
	const uint32_t unknown;
	const uint32_t height;
	const uint32_t width;
	const uint64_t unknown2;
	const uint32_t bitmap_size;
	const uint64_t unknown3;
	const uint64_t zero;
} header = {
	.BM = 0x4D42,
	.total_size = BITMAP_SIZE + 54,
	.offset = 54,
	.unknown = 40,
	.height = HEIGHT,
	.width = WIDTH,
	.unknown2 = 0x180001,
	.bitmap_size = BITMAP_SIZE,
	.unknown3 = 0xB1300000B13
};

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
