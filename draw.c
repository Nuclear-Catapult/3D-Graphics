#include "triangle.h"

int main()
{
	alloc_bitmap();
	triangle_t t = { (Vertice) {100, 100},
			 (Vertice) {400, 300},
			 (Vertice) {100, 400} };
	draw_triangle(&t);
	write_bmp();
	free_bitmap();
}
