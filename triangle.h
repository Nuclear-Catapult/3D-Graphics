#pragma once
#include "vertice.h"

struct Triangle3D {
	float ar[12];
	uint32_t color;
};


union Triangle{
	struct {
		struct Vertice v1;
		struct Vertice v2;
		struct Vertice v3;
	};
	float ar[6];
};

void draw_triangle(struct Triangle3D *t3D);
