#pragma once
#include "vertice.h"

struct Triangle{
		struct Vertice v1;
		struct Vertice v2;
		struct Vertice v3;
};

void draw_triangle(struct Triangle *this, uint32_t color);
