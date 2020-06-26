#include "triangle.h"

int main()
{
	alloc_bitmap();
	struct Triangle t = { (union Vertice) {100, 100},
			 (union Vertice) {400, 400},
			 (union Vertice) {300, 150} };
	draw_triangle(&t);
	write_bmp();
	free_bitmap();
}
