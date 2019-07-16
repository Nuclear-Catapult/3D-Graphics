#include <stddef.h>
#include <stdint.h>

typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_t;

typedef struct
{
	pixel_t *pixels;
	uint16_t width;
	uint16_t height;
} bitmap_t;

extern bitmap_t image;
