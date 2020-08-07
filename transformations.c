#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "transformations.h"

float projection[] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, -1/DISTANCE,
	0, 0, 0, 1
};

void project2D(float* matrix3D, float* matrix2D, uint32_t p_count)
{
	memset(matrix2D, 0, sizeof(float)*p_count*4);
	for (int i = 0; i < p_count; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				matrix2D[4*i+j] += projection[k*4+j] * matrix3D[i*4+k];
}

#define _i_ 0
#define _j_ 1
#define _k_ 2
#define _r_ 3

// https://www.youtube.com/watch?v=zjMuIxRvygQ&t=4m01s
void derive_q(float q[4], float axis[3], float radians)
{
	radians /= 2;
	float sin_multiplier = sin(radians);
	for (int i = _i_; i <= _k_; i++)
		q[i] = sin_multiplier * axis[i];
	q[_r_] = cos(radians);
}

// https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation##Quaternion-derived_rotation_matrix
void derive_R(float R[9], float q[4])
{
	// In this program, s = 2||q||^-2 whereas on Wikipedia, s = ||q||^-2
	float s = sqrt(q[_i_]*q[_i_] + q[_j_]*q[_j_] + q[_k_]*q[_k_] + q[_r_]*q[_r_]);
	s = 2 / (s*s);
	R[0] = 1 - s*(q[_j_]*q[_j_] + q[_k_]*q[_k_]);
	R[1] =     s*(q[_i_]*q[_j_] - q[_k_]*q[_r_]);
	R[2] =     s*(q[_i_]*q[_k_] + q[_j_]*q[_r_]);
	R[3] =     s*(q[_i_]*q[_j_] + q[_k_]*q[_r_]);
	R[4] = 1 - s*(q[_i_]*q[_i_] + q[_k_]*q[_k_]);
	R[5] =     s*(q[_j_]*q[_k_] - q[_i_]*q[_r_]);
	R[6] =     s*(q[_i_]*q[_k_] - q[_j_]*q[_r_]);
	R[7] =     s*(q[_j_]*q[_k_] + q[_i_]*q[_r_]);
	R[8] = 1 - s*(q[_i_]*q[_i_] + q[_j_]*q[_j_]);
}

void rotate(float R[9], float* p, uint32_t p_count)
{
	float temp_vector[3];
	for (int i = 0; i < p_count; i++) {
		memset(temp_vector, 0, sizeof(temp_vector));
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				temp_vector[j] += R[3*j+k]*p[k+4*i];
		memcpy(p+4*i, temp_vector, sizeof(float)*3);
	}
}

#undef _i_
#undef _j_
#undef _k_
#undef _r_
/*
int main()
{

	float R[] = {
		1, 2, 3,
		5, 7, 11,
		13, 17, 19
	};
	float p[] = {
		4, 5, 6, 0,
		7, 8, 9, 0,
		10, 11, 12, 0,
		13, 14, 15, 0
	};

	rotate(R, p, 4);

	printf("p...\n");
	for (int i = 0; i < 12; i++)
		printf("%f\n", p[i]);
	printf("\n");

	float D[] = {
		3, 1, 5, 1,
		5, 1, 5, 1,
		5, 0, 5, 1,
		3, 0, 5, 1,
		3, 1, 4, 1,
		5, 1, 4, 1,
		5, 0, 4, 1,
		3, 0, 4, 1
	};
	float PD[32];
	project2D(D, PD, 8);
	for (int i = 0; i < 32; i++)
	printf("%f\n", PD[i]);
}
*/
