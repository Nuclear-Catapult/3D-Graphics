#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

void set_pix(uint16_t, uint16_t, uint8_t, uint8_t, uint8_t);

void line(uint16_t y, uint16_t right, uint16_t left)
{
	uint16_t start = image.width * y + right;
	for (int i = start; i < start + left - right; i++) {
		pixel_t *pixel = image.pixels + i;
		pixel->red = 255;
		pixel->green = 0;
		pixel->blue = 0;
	}
}

void blue_line(uint16_t y, uint16_t right, uint16_t left)
{
	uint16_t start = image.width * y + right;
	for (int i = start; i < start + left - right; i++) {
		pixel_t *pixel = image.pixels + i;
		pixel->red = 0;
		pixel->green = 0;
		pixel->blue = 255;
	}
}

typedef struct { uint16_t x;
		 uint16_t y; } Vertice;

void swap(Vertice *num1, Vertice *num2)
{
	Vertice temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void fillBottomFlatTriangle(Vertice v1, Vertice v2, uint16_t v3DOTx)
{
	int myNum = 1996;
	// v2.y == v3.y
	float invslope1 = (float) (v2.x - v1.x) / (v2.y - v1.y);
	float invslope2 = (float) (v3DOTx - v1.x) / (v2.y - v1.y);

	float curx1 = v1.x;
	float curx2 = v1.x;

	for (int i = v1.y; i <= v2.y; i++) {
		line(i, (uint16_t)curx1, (uint16_t)curx2);
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

void fillTopFlatTriangle(Vertice v1, uint16_t v2DOTx, Vertice v3)
{
	// v1.y == v2.y
	float invslope1 = (float) (v3.x - v1.x) / (v3.y - v1.y);
	float invslope2 = (float) (v3.x - v2DOTx) / (v3.y - v1.y);

	float curx1 = v3.x;
	float curx2 = v3.x;

	for (int i = v3.y; i > v1.y; i--) {
		blue_line(i, (uint16_t)curx1, (uint16_t)curx2);
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

void triangle(Vertice v1, Vertice v2, Vertice v3)
{
	if (v1.y > v2.y)
		swap(&v1, &v2);
	if (v2.y > v3.y)
		swap(&v2, &v3);
	if (v1.y > v2.y)
		swap(&v1, &v2);
	
	// v1.y <= v2.y <= v3.y
	if (v2.y == v3.y) {
		fillBottomFlatTriangle(v1, v2, v3.x);
	} else if (v1.y == v2.y) {
		fillTopFlatTriangle(v1, v2.x, v3);
	} else {
		uint16_t newX = (uint16_t) (v1.x +
		((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x));
		fillBottomFlatTriangle(v1, v2, newX);
		fillTopFlatTriangle(v2, newX, v3);
	}
		
	
}

void draw()
{
	image.width = 100;
	image.height = 100;

	image.pixels = calloc(image.width * image.height, sizeof(pixel_t));
	
	memset(image.pixels, '0', image.height*image.width*sizeof(pixel_t));

	triangle((Vertice) {90, 10}, (Vertice) {50, 50}, (Vertice) {99, 99});

	line(60, 0, 99);
	line(61, 1, 98);
	line(62, 2, 97);
	line(63, 3, 96);
}
