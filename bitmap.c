#include "bitmap.h"

const uint16_t padding = 0;
const uint16_t BM = 0x4D42;
const uint32_t total_size = BITMAP_SIZE + 54;
const uint32_t reserved = 0;
const uint32_t offset = 54;
const uint32_t unknown = 40;
const uint32_t height = HEIGHT;
const uint32_t width = WIDTH;
const uint32_t unknown2 = 0x180001;
const uint32_t zero_padding = 0;
const uint32_t bitmap_size = BITMAP_SIZE;
const uint64_t unknown3 = 0xB1300000B13;
const uint64_t zero_padding2 = 0;

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
	fwrite(&BM, sizeof(char), offset, f);
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
