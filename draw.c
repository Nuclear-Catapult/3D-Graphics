#include <stdio.h>
#include <stdlib.h>

#include "triangle.h"
#include "bitmap.h"

const int distance = 1000;

#define RED 0xff0000
#define YELLOW 0xffff00
#define GREEN 0x00ff00
#define CYAN 0x00ffff
#define BLUE 0x0000ff
#define PINK 0xff00ff

struct Triangle3D {
	float ar[12];
	uint32_t color;
};

int compare_function(const void *v_a, const void *v_b)
{
	struct Triangle3D *a = (struct Triangle3D *) v_a;
	struct Triangle3D *b = (struct Triangle3D *) v_b;
	return a->ar[2] + a->ar[6] + a->ar[10] - b->ar[2] - b->ar[6] - b->ar[10];
}

int main()
{
	struct Triangle3D cube[12] = {
		{{// 0
			-1, -1, -1, 0,
			-1, 1, -1, 0,
			1, -1, -1, 0}, .color = RED},
		{{// 1
			-1, 1, -1, 0,
			1, 1, -1, 0,
			1, -1, -1, 0}, .color = RED},
		{{// 2
			-1, -1, 1, 0,
			-1, 1, 1, 0,
			1, -1, 1, 0}, .color = YELLOW},
		{{// 3
			-1, 1, 1, 0,
			1, 1, 1, 0,
			1, -1, 1, 0}, .color = YELLOW},
		{{// 4
			-1, -1, -1, 0,
			-1, 1, -1, 0,
			-1, -1, 1, 0}, .color = GREEN},
		{{// 5
			-1, 1, -1, 0,
			-1, 1, 1, 0,
			-1, -1, 1, 0}, .color = GREEN},
		{{// 6
			1, -1, -1, 0,
			1, 1, -1, 0,
			1, -1, 1, 0}, .color = CYAN},
		{{// 7
			1, 1, -1, 0,
			1, 1, 1, 0,
			1, -1, 1, 0}, .color = CYAN},
		{{// 8
			-1, -1, -1, 0,
			1, -1, -1, 0,
			-1, -1, 1, 0}, .color = BLUE},
		{{// 9
			1, -1, -1, 0,
			-1, -1, 1, 0,
			1, -1, 1, 0}, .color = BLUE},
		{{// 10
			-1, 1, -1, 0,
			1, 1, -1, 0,
			-1, 1, 1, 0}, .color = PINK},
		{{// 11
			1, 1, -1, 0,
			-1, 1, 1, 0,
			1, 1, 1, 0}, .color = PINK}
	};

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			cube[i].ar[j] *= 50;

	qsort(cube, 12, sizeof(struct Triangle3D), compare_function);

	float p_cube[6];
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 3; j++) {
			float divisor = 1 - (cube[i].ar[4*j+2] + 100) / distance;
			p_cube[j*2  ] = (cube[i].ar[4*j] + 200) / divisor;
			p_cube[j*2+1] = (cube[i].ar[4*j+1] + 200) / divisor;
		}
		draw_triangle((struct Triangle*)p_cube, cube[i].color);
	}

	write_bmp();
}
