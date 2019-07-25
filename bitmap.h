#pragma once
#include "vertice.h"

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_t;

#define HEIGHT 500
#define WIDTH 500
#define BITMAP_SIZE HEIGHT * WIDTH * sizeof(pixel_t)
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
	.unknown3 = 0xB1300000B13,
};

extern pixel_t *bitmap;
extern uint16_t *depth_buffer;

void alloc_bitmap();
void write_bmp();
void free_bitmap();
