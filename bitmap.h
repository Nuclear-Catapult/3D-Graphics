#pragma once

#include "vertice.h"

#define HEIGHT 500
#define WIDTH 500
#define BITMAP_SIZE HEIGHT * WIDTH * sizeof(pixel_t)

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_t;


extern pixel_t *bitmap;
extern uint16_t *depth_buffer;

void alloc_bitmap();
void write_bmp();
void free_bitmap();
