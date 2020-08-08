#include <stdio.h>
#include <stdlib.h>

#include "triangle.h"
#include "bitmap.h"
#include "transformations.h"

#define RED 0xff0000
#define YELLOW 0xffff00
#define GREEN 0x00ff00
#define CYAN 0x00ffff
#define BLUE 0x0000ff
#define PINK 0xff00ff

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

	float q[4];
	float axis[] = {0, 0, 1};
	derive_q(q, axis, 0.3);
	float R[9];
	derive_R(R, q);

	for (int i = 0; i < 12; i++)
		rotate(R, cube[i].ar, 3);

	float axis2[] = {0, 1, 0};
	derive_q(q, axis2, 0.05);
	derive_R(R, q);

	for (int frame = 0; frame < 1000; frame++) {
		for (int i = 0; i < 12; i++) {
			rotate(R, cube[i].ar, 3);
			for (int j = 0; j < 3; j++) {
				cube[i].ar[j*4] += 200;
				cube[i].ar[j*4+1] += 200;
				cube[i].ar[j*4+2] += 200;
			}
		}
		qsort(cube, 12, sizeof(struct Triangle3D), compare_function);

		for (int i = 0; i < 12; i++) {
			draw_triangle(&cube[i]);
			for (int j = 0; j < 3; j++) {
				cube[i].ar[j*4] -= 200;
				cube[i].ar[j*4+1] -= 200;
				cube[i].ar[j*4+2] -= 200;
			}
		}
		write_bmp();
	}
}
