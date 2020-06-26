#include "vertice.h"

void swap(union Vertice *v1, union Vertice *v2)
{
	union Vertice temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}
