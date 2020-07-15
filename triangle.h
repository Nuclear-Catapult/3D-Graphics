#pragma once
#include "vertice.h"

#define RED 0xff0000
#define YELLOW 0xffff00
#define GREEN 0x00ff00
#define CYAN 0x00ffff
#define BLUE 0x0000ff
#define PINK 0xff00ff

struct Triangle{
	struct Vertice v1;
	struct Vertice v2;
	struct Vertice v3;
	uint16_t color;
};

void draw_triangle(struct Triangle *this);
