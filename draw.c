#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"

void set_pix(uint16_t, uint16_t, uint8_t, uint8_t, uint8_t);
int save_png_to_file(const char *path);

int frame = 0;

void line(uint16_t y, uint16_t right, uint16_t left)
{
	int start = image.width * y + left;
	for (int i = start; i <= start - left + right; i++) {
		pixel_t *pixel = image.pixels + i;
		pixel->red = 255;
		pixel->green = 0;
		pixel->blue = 0;
	}
}

void blue_line(uint16_t y, uint16_t right, uint16_t left)
{
	int start = image.width * y + left;
	for (int i = start; i <= start - left + right; i++) {
		pixel_t *pixel = image.pixels + i;
		pixel->red = 0;
		pixel->green = 0;
		pixel->blue = 255;
	}
	/*char str[12];
	sprintf(str, "pic%04d.png", frame++);
    if (save_png_to_file(str))
	fprintf(stderr, "Error writing file.\n"); */
}

typedef struct { uint16_t x;
		 uint16_t y; } Vertice;
Vertice centroid;

void swap(Vertice *num1, Vertice *num2)
{
	Vertice temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
float temp;
void fillBottomFlatTriangle(Vertice v1, Vertice v2, uint16_t v3DOTx)
{
	// v2.y == v3.y
	float invslope1 = (float) (v2.x - v1.x) / (v2.y - v1.y);
	float invslope2 = (float) (v3DOTx - v1.x) / (v2.y - v1.y);
	if (invslope2 > invslope1) {
		temp = invslope1;
		invslope1 = invslope2;
		invslope2 = temp;
	}

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
	if (invslope2 < invslope1) {
		temp = invslope1;
		invslope1 = invslope2;
		invslope2 = temp;
	}

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

void circle(Vertice center, uint16_t radius)
{
	const float twelthofPI = 3.14159265 / 12;
	Vertice outerVert[24];
	outerVert[0] = (Vertice) { center.x + radius, center.y };
	outerVert[6] = (Vertice) { center.x, center.y + radius };
	outerVert[12] = (Vertice) { center.x - radius, center.y };
	outerVert[18] = (Vertice) { center.x, center.y - radius };

	for (int quadrant = 0; quadrant < 4; quadrant++)
		for (int i = 1; i < 6; i++) {
			float input = twelthofPI*quadrant*6+i*twelthofPI;
			outerVert[quadrant*6+i] = (Vertice) { (uint16_t) (cos(input)*radius+center.x), (uint16_t) (sin(input)*radius+center.y) };
		}
	for (int i = 1; i < 24; i++) {
		triangle(center, outerVert[i], outerVert[i-1]);
	}
	triangle(center, outerVert[0], outerVert[23]);
}

Vertice rotate(Vertice v, float theta)
{
	v.x -= centroid.x;
	v.y -= centroid.y;

	float sine = sin(theta);
	float cosine = cos(theta);
	float temp = v.x;

	v.x = (uint16_t)(v.x*cosine - v.y*sine);
	v.y = (uint16_t)(temp*sine + v.y*cosine);

	v.x += centroid.x;
	v.y += centroid.y;

	return v;
}

void draw()
{
	image.width = 500;
	image.height = 500;

	image.pixels = calloc(image.width * image.height, sizeof(pixel_t));

	Vertice v1 = { 250, 200 };
	Vertice v2 = { 400, 400 };
	Vertice v3 = { 100, 330 };

	centroid.x = (v1.x + v2.x + v3.x) / 3;
	centroid.y = (v1.y + v2.y + v3.y) / 3;

	for (float i = 0; i < 50; i+=0.05) {
		memset(image.pixels, 0, image.height*image.width*sizeof(pixel_t));
		triangle(rotate(v1, i), rotate(v2, i), rotate(v3, i));
		char str[12];
		sprintf(str, "pic%04d.png", frame++);
    		save_png_to_file(str);
	}
}
