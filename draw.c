#include "triangle.h"
#include "bitmap.h"

const int distance = 1000;

int main()
{
	float cube[144] = {
		// RED
		-1, -1, -1, 0,
		-1, 1, -1, 0,
		1, -1, -1, 0,
		-1, 1, -1, 0,
		1, 1, -1, 0,
		1, -1, -1, 0,
		// YELLOW
		-1, -1, 1, 0,
		-1, 1, 1, 0,
		1, -1, 1, 0,
		-1, 1, 1, 0,
		1, 1, 1, 0,
		1, -1, 1, 0,
		// GREEN
		-1, -1, -1, 0,
		-1, 1, -1, 0,
		-1, -1, 1, 0,
		-1, 1, -1, 0,
		-1, 1, 1, 0,
		-1, -1, 1, 0,
		// CYAN
		1, -1, -1, 0,
		1, 1, -1, 0,
		1, -1, 1, 0,
		1, 1, -1, 0,
		1, 1, 1, 0,
		1, -1, 1, 0,
		// BLUE
		-1, -1, -1, 0,
		1, -1, -1, 0,
		-1, -1, 1, 0,
		1, -1, -1, 0,
		-1, -1, 1, 0,
		1, -1, 1, 0,
		// PINK
		-1, 1, -1, 0,
		1, 1, -1, 0,
		-1, 1, 1, 0,
		1, 1, -1, 0,
		-1, 1, 1, 0,
		1, 1, 1, 0
	};

	uint32_t color_buffer[] = {
		RED, RED,
		YELLOW, YELLOW,
		GREEN, GREEN,
		CYAN, CYAN,
		BLUE, BLUE,
		PINK, PINK
	};

	for (int i = 0; i < 144; i++)
		cube[i] *= 50;

	float p_cube[72];

	for (int i = 0; i < 36; i++) {
		float divisor = 1 - (cube[4*i+2] + 100) / distance;
		p_cube[2*i  ] = (cube[4*i  ] + 200) / divisor;
		p_cube[2*i+1] = (cube[4*i+1] + 200) / divisor;
	}

	for (int i = 0; i < 12; i++)
		draw_triangle((union Triangle*)&p_cube[i*6], color_buffer[i]);

	write_bmp();
}
