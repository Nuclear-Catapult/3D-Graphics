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

void print_color(uint32_t color);

int compare_function(const void *v_a, const void *v_b)
{
	// quick-and-dirty
	const struct Triangle3D *t_a = (const struct Triangle3D *) v_a;
	const struct Triangle3D *t_b = (const struct Triangle3D *) v_b;
	const float *a = t_a->ar;
	const float *b = t_b->ar;

	float midpoint1[3] = {0};
	float midpoint2[3] = {0};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			midpoint1[j] += a[i * 4 + j];
			midpoint2[j] += b[i * 4 + j];
		}
	}

	for (int i = 0; i < 3; i++) {
		midpoint1[i] /= 3;
		midpoint2[i] /= 3;
	}

	midpoint1[2] -= 1000;
	midpoint2[2] -= 1000;

	float distance1 = 0;
	float distance2 = 0;

	for (int i = 0; i < 3; i++) {
		distance1 += midpoint1[i] * midpoint1[i];
		distance2 += midpoint2[i] * midpoint2[i];
	}
	return sqrt(distance1) - sqrt(distance2);
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

	for (int frame = 0; frame < FRAMES; frame++) {
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
			/*{// logging: It's recommended to set FRAMES to 1 when uncommented
				float midpoint[3];
				memset(midpoint, 0, 3*sizeof(float));
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						midpoint[k] += (cube[i].ar[j*4+k]/3);
				for (int j = 0; j < 3; j++)
					printf("%.2f\t", midpoint[j]);
				midpoint[2] -= 1000;
				float distance = 0;
				for (int j = 0; j < 3; j++)
					midpoint[j] = midpoint[j]*midpoint[j];
				distance = sqrt(midpoint[0]+midpoint[1]+midpoint[2]);
				printf("dist = %.2f\t", distance);
				print_color(cube[i].color);
			}*/
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
