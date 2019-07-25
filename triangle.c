#include "triangle.h"

void fillTopFlatTriangle(Vertice v1, Vertice v2, uint16_t v3DOTx)
{
	// v2.y == v3.y
	float invslope1 = (float) (v2.x - v1.x) / (v2.y - v1.y);
	float invslope2 = (float) (v3DOTx - v1.x) / (v2.y - v1.y);
	if (invslope1 < invslope2)
		swap((Vertice*)&invslope1, (Vertice*)&invslope2);

	float curx1 = v1.x;
	float curx2 = v1.x;

	for (int i = v1.y; i <= v2.y; i++) {
		draw_line(i, (uint16_t)curx1, (uint16_t)curx2);
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

void fillBottomFlatTriangle(Vertice v1, uint16_t v2DOTx, Vertice v3)
{
	// v1.y == v2.y
	float invslope1 = (float) (v3.x - v1.x) / (v3.y - v1.y);
	float invslope2 = (float) (v3.x - v2DOTx) / (v3.y - v1.y);
	if (invslope1 > invslope2)
		swap((Vertice*)&invslope1, (Vertice*)&invslope2);

	float curx1 = v3.x;
	float curx2 = v3.x;

	for (int i = v3.y; i > v1.y; i--) {
		draw_line(i, (uint16_t)curx1, (uint16_t)curx2);
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

void draw_triangle(triangle_t *this)
{
	if (this->v1.y > this->v2.y)
		swap(&this->v1, &this->v2);
	if (this->v2.y > this->v3.y)
		swap(&this->v2, &this->v3);
	if (this->v1.y > this->v2.y)
		swap(&this->v1, &this->v2);

	// v1.y <= v2.y <= v3.y
	if (this->v2.y == this->v3.y) {
		fillTopFlatTriangle(this->v1, this->v2, this->v3.x);
	} else if (this->v1.y == this->v2.y) {
		fillBottomFlatTriangle(this->v1, this->v2.x, this->v3);
	} else {
		uint16_t newX = (uint16_t) (this->v1.x +
		((float)(this->v2.y - this->v1.y) / (float)(this->v3.y - this->v1.y)) * (this->v3.x - this->v1.x));
		fillTopFlatTriangle(this->v1, this->v2, newX);
		fillBottomFlatTriangle(this->v2, newX, this->v3);
	}
}
