#pragma once

#include <stdint.h>

#include "triangle.h"

void set_color(uint32_t color);

void draw_line(uint16_t x, uint16_t y, uint16_t right, const union Triangle* t2D, const struct Triangle3D* t3D);
