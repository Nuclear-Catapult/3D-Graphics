#pragma once
#include <stdint.h>

union Vertice {
	// This feature is an anonymous struct added to C11
	struct {
		uint16_t x;
		uint16_t y;
		uint16_t z;
		uint16_t w;
	};
	uint64_t vert64;
	// insert floats only when using swap function
	float swap;
};

void swap(union Vertice *v1, union Vertice *v2);
