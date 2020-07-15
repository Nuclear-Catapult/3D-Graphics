#include "triangle.h"
#include "bitmap.h"

int main()
{
	struct Triangle t = { 
		.v1 = { .x = 100, .y = 100},
		.v2 = { .x = 400, .y = 400},
		.v3 = { .x = 300, .y = 150},
		.color = GREEN
	};

	float t2[] = {
		100, 100, 0, 0,
		400, 400, 0, 0,
		300, 150, 0, 0
	};

	draw_triangle(&t);
	write_bmp();
}
