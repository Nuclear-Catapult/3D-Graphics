#include "triangle.h"
#include "line.h"

#define DISTANCE 1000

// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html

void fillTopFlatTriangle(const union Triangle half, const union Triangle *t2D, const struct Triangle3D *t3D)
{
	// v2.y == v3.y
	float invslope1 = (half.v2.x - half.v1.x) / (half.v2.y - half.v1.y);
	float invslope2 = (half.v3.x - half.v1.x) / (half.v2.y - half.v1.y);
	if (invslope1 < invslope2)
		swap((struct Vertice*)&invslope1, (struct Vertice*)&invslope2);

	float curx1 = half.v1.x;
	float curx2 = half.v1.x;

	for (int i = half.v1.y; i <= half.v2.y; i++) {
		draw_line((uint16_t)curx2, i, (uint16_t)curx1, t2D, t3D);
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

void fillBottomFlatTriangle(const union Triangle half, union Triangle *t2D, struct Triangle3D *t3D)
{
	// v1.y == v2.y
	float invslope1 = (half.v3.x - half.v1.x) / (half.v3.y - half.v1.y);
	float invslope2 = (half.v3.x - half.v2.x) / (half.v3.y - half.v1.y);
	if (invslope1 > invslope2)
		swap((struct Vertice*)&invslope1, (struct Vertice*)&invslope2);

	float curx1 = half.v3.x;
	float curx2 = half.v3.x;

	for (int i = half.v3.y; i > half.v1.y; i--) {
		draw_line((uint16_t)curx2, i, (uint16_t)curx1, t2D, t3D);
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

void draw_triangle(struct Triangle3D *t3D)
{
	set_color(t3D->color);
	union Triangle this;
	for (int j = 0; j < 3; j++) {
		float divisor = 1 - (t3D->ar[4*j+2] + 100) / DISTANCE;
		this.ar[j*2  ] = (t3D->ar[4*j] + 200) / divisor;
		this.ar[j*2+1] = (t3D->ar[4*j+1] + 200) / divisor;
	}

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
	fillTopFlatTriangle((union Triangle) { .v1 = this.v1, .v2 = this.v2, .v3.x = newX}, &this, t3D);
	fillBottomFlatTriangle((union Triangle) { .v1 = this.v2, .v2.x = newX, .v3 = this.v3 }, &this, t3D);
}
