#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"

#define M_PI 3.14159265358979323846

float to_radians(float deg);

void identity(float elements[]);

void
perspective(float elements[],
		float fov,
		float aspect_ratio,
		float near,
		float far);

void translate(float elements[], float x, float y, float z);
void rotate(float elements[], float angle, vec3 axis);
void mat4_multiply(float res[], float mat1[], float mat2[]);
void mat4_print(float mat[]);

#endif
