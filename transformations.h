#pragma once

#define DISTANCE 1000

void project2D(float* matrix3D, float* matrix2D, uint32_t p_count);

void derive_q(float q[4], float axis[3], float radians);

void derive_R(float R[9], float q[4]);

void rotate(float R[9], float* p, uint32_t p_count);
