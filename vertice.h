#pragma once
#include <stdint.h>

struct Vertice {
//	struct {
		float x;
		float y;
		float z;
		float w;
//	};
	//uint64_t vert64;
	// insert floats only when using swap function
};

void swap(struct Vertice *v1, struct Vertice *v2);
