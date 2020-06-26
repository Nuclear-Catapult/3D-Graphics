#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define HEIGHT 500
#define WIDTH 500
#define BITMAP_SIZE HEIGHT * WIDTH * sizeof(struct Pixel)

struct Pixel {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}*bitmap;

uint16_t *depth_buffer;

void alloc_bitmap();
void write_bmp();
void free_bitmap();
