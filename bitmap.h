#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define HEIGHT 500
#define WIDTH 500

struct Pixel {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct Pixel bitmap[HEIGHT * WIDTH];

// uint16_t *depth_buffer;

void write_bmp();
