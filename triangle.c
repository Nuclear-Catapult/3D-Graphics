#include "triangle.h"
#include "line.h"

#define DISTANCE 1000

// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html

void fillTopFlatTriangle(struct Vertice v1, struct Vertice v2, float v3DOTx)
{
	// v2.y == v3.y
	float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
	float invslope2 = (v3DOTx - v1.x) / (v2.y - v1.y);
	if (invslope1 < invslope2)
		swap((struct Vertice*)&invslope1, (struct Vertice*)&invslope2);

	float curx1 = v1.x;
	float curx2 = v1.x;

	for (int i = v1.y; i <= v2.y; i++) {
		draw_line((uint16_t)curx2, i, (uint16_t)curx1);
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

void fillBottomFlatTriangle(struct Vertice v1, float v2DOTx, struct Vertice v3)
{
	// v1.y == v2.y
	float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
	float invslope2 = (v3.x - v2DOTx) / (v3.y - v1.y);
	if (invslope1 > invslope2)
		swap((struct Vertice*)&invslope1, (struct Vertice*)&invslope2);

	float curx1 = v3.x;
	float curx2 = v3.x;

	for (int i = v3.y; i > v1.y; i--) {
		draw_line((uint16_t)curx2, i, (uint16_t)curx1);
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

void draw_triangle(struct Triangle3D *t3D)
{
	union Triangle this;
	for (int j = 0; j < 3; j++) {
		float divisor = 1 - (t3D->ar[4*j+2] + 100) / DISTANCE;
		this.ar[j*2  ] = (t3D->ar[4*j] + 200) / divisor;
		this.ar[j*2+1] = (t3D->ar[4*j+1] + 200) / divisor;
	}
	set_color(t3D->color);

	if (this.v1.y > this.v2.y)
		swap(&this.v1, &this.v2);
	if (this.v2.y > this.v3.y)
		swap(&this.v2, &this.v3);
	if (this.v1.y > this.v2.y)
		swap(&this.v1, &this.v2);

	// v1.y <= v2.y <= v3.y
	float newX = (this.v1.x +
	(this.v2.y - this.v1.y) / (this.v3.y - this.v1.y) *
	(this.v3.x - this.v1.x));
	fillTopFlatTriangle(this.v1, this.v2, newX);
	fillBottomFlatTriangle(this.v2, newX, this.v3);
}
