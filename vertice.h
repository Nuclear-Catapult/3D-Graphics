#pragma once
#include <stdint.h>

struct Vertice {
		float x;
		float y;
};

void swap(struct Vertice *v1, struct Vertice *v2);
void swap3D(float v1[3], float v2[3]);
