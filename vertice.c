#include "vertice.h"

void swap(Vertice *v1, Vertice *v2)
{
	Vertice temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}
