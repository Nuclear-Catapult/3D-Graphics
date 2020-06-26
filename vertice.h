#pragma once
#include <stdint.h>

typedef union {
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
} Vertice;

void swap(Vertice *v1, Vertice *v2);
