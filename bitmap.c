#include "bitmap.h"

#define BITMAP_SIZE HEIGHT * WIDTH * sizeof(struct Pixel)
#define HEADER_SIZE 54

const uint16_t padding = 0;
const uint16_t BM = 0x4D42;
const uint32_t total_size = BITMAP_SIZE + HEADER_SIZE;
const uint32_t reserved = 0;
const uint32_t offset = HEADER_SIZE;
const uint32_t unknown = 40;
const uint32_t height = HEIGHT;
const uint32_t width = WIDTH;
const uint32_t unknown2 = 0x180001;
const uint32_t zero_padding = 0;
const uint32_t bitmap_size = BITMAP_SIZE;
const uint64_t unknown3 = 0xB1300000B13;
const uint64_t zero_padding2 = 0;

struct Pixel bitmap[HEIGHT * WIDTH] = {0};

void write_bmp()
{
	static char str[12];
	static int frame = 0;
	sprintf(str, "pic%04d.bmp", frame++);

	FILE *f = fopen(str, "wb");
	fwrite(&BM, 1, offset, f);
	fwrite(bitmap, 1, BITMAP_SIZE, f);

	// clear bitmap and max Z_Buffer
	memset(bitmap, 0, BITMAP_SIZE);

	fclose(f);
}
