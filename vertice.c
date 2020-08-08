#include <stdio.h>
#include <string.h>

#include "vertice.h"

void swap(struct Vertice *v1, struct Vertice *v2)
{
	struct Vertice temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

void swap3D(float v1[3], float v2[3])
{
	float temp[3];
	memcpy(temp, v1, 3*sizeof(float));
	memcpy(v1, v2, 3*sizeof(float));
	memcpy(v2, temp, 3*sizeof(float));
}
