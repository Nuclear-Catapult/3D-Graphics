#include <stdio.h>
#include <string.h>

#include "vertice.h"

void swap(struct Vertice *v1, struct Vertice *v2)
{
	struct Vertice temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}
