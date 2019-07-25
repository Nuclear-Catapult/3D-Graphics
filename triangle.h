#pragma once
#include "line.h"
#include "vertice.h"

typedef struct {
	Vertice v1;
	Vertice v2;
	Vertice v3;
} triangle_t;

void draw_triangle(triangle_t *this);
