#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "triangle.h"
#include "bitmap.h"
#include "transformations.h"

#define RED 0xff0000
#define YELLOW 0xffff00
#define GREEN 0x00ff00
#define CYAN 0x00ffff
#define BLUE 0x0000ff
#define PINK 0xff00ff

#define FRAMES 1000

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

	for (int frame = 0; frame < FRAMES; frame++) {
		for (int i = 0; i < 12; i++) {
			rotate(R, cube[i].ar, 3);
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					cube[i].ar[j*4+k] += 200;
		}
		for (int i = 0; i < 12; i++) {
			draw_triangle(&cube[i]);
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					cube[i].ar[j*4+k] -= 200;
		}
		write_bmp();
	}
}

// great for debugging
void print_color(uint32_t color) {
	switch (color) {
		case 0xff0000:
			printf("RED\n");
			break;
		case 0xffff00:
			printf("YELLOW\n");
			break;
		case 0x00ff00:
			printf("GREEN\n");
			break;
		case 0x00ffff:
			printf("CYAN\n");
			break;
		case 0x0000ff:
			printf("BLUE\n");
			break;
		case 0xff00ff:
			printf("PINK\n");
			break;
		default:
			fprintf(stderr, "Not a valid color"), exit(1);
	};
}
