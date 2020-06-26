#pragma once
#include "vertice.h"

struct Triangle{
	union Vertice v1;
	union Vertice v2;
	union Vertice v3;
};

void draw_triangle(struct Triangle *this);
