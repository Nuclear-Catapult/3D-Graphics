#include "line.h"
#include "bitmap.h"

_Thread_local struct Pixel current_color;

void set_color(uint32_t color)
{
	current_color.blue = color % 256;
	current_color.green = (color >> 8) % 256;
	current_color.red = (color >> 16) % 256;
}

void draw_line(uint16_t x, uint16_t y, uint16_t right, const union Triangle *t2D, const struct Triangle3D *t3D)
{
	int32_t start = WIDTH * y;
	// wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
	float lambda[3];
	float det_T =
		(t2D->v2.y-t2D->v3.y)*(t2D->v1.x-t2D->v3.x)+(t2D->v3.x-t2D->v2.x)*(t2D->v1.y-t2D->v3.y);
	while (x <= right) {
		lambda[0] = 
			((t2D->v2.y-t2D->v3.y)*(x-t2D->v3.x)+(t2D->v3.x-t2D->v2.x)*(y-t2D->v3.y)) / det_T;
		lambda[1] = 
			((t2D->v3.y-t2D->v1.y)*(x-t2D->v3.x)+(t2D->v1.x-t2D->v3.x)*(y-t2D->v3.y)) / det_T;
		lambda[2] =
			1 - lambda[0] - lambda[1];

		float proj_x = 0;
		float proj_y = 0;
		float proj_z = 0;
		
		for (int i = 0; i < 3; i++) {
			proj_x += t3D->ar[i*4  ]*lambda[i];
			proj_y += t3D->ar[i*4+1]*lambda[i];
			proj_z += t3D->ar[i*4+2]*lambda[i];
		}

		proj_z -= 1000;
		uint32_t sqrd_distance = (uint32_t)
			(proj_x*proj_x + proj_y*proj_y + proj_z*proj_z);

		if (Z_Buffer[start+x] > sqrd_distance) {
			bitmap[start+x] = current_color;
			Z_Buffer[start+x] = sqrd_distance;
		}
		x++;
	}
}
