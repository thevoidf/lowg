#include <math.h>
#include "mat4.h"
#include <stdio.h>

float to_radians(float deg)
{
	return (float) (deg * (M_PI / 180.0f));
}

void mat4_identity(float elements[])
{
	int i;
	for (i = 0; i < 4*4; i++)
		elements[i] = 0.0f;

	elements[0 + 0 * 4] = 1.0f;
	elements[1 + 1 * 4] = 1.0f;
	elements[2 + 2 * 4] = 1.0f;
	elements[3 + 3 * 4] = 1.0f;
}

void mat4_perspective(float elements[],
		float fov,
		float aspect_ratio,
		float near,
		float far)
{
	mat4_identity(elements);

	float q = 1.0f / tan(to_radians(0.5f * fov));
	float a = q / aspect_ratio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	elements[0 + 0 * 4] = a;
	elements[1 + 1 * 4] = q;
	elements[2 + 2 * 4] = b;
	elements[3 + 2 * 4] = -1.0f;
	elements[2 + 3 * 4] = c;
}

void
mat4_translate(float elements[], float x, float y, float z)
{
	mat4_identity(elements);

	elements[0 + 3 * 4] = x;
	elements[1 + 3 * 4] = y;
	elements[2 + 3 * 4] = z;
}

void mat4_rotate(float elements[], float angle, vec3 axis)
{
	mat4_identity(elements);

	float r = to_radians(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	elements[0 + 0 * 4] = x * x * omc + c;
	elements[0 + 1 * 4] = y * x * omc + z * s;
	elements[0 + 2 * 4] = x * z * omc - y * s;

	elements[1 + 0 * 4] = x * y * omc - z * s;
	elements[1 + 1 * 4] = y * y * omc + c;
	elements[1 + 2 * 4] = y * z * omc + x * s;

	elements[2 + 0 * 4] = x * z * omc + y * s;
	elements[2 + 1 * 4] = y * z * omc - x * s;
	elements[2 + 2 * 4] = z * z * omc + c;
}

void mat4_multiply(float res[], float mat1[], float mat2[])
{
	int row, col, e;

	for (col = 0; col < 4; col++) {
		for (row = 0; row < 4; row++) {
			float sum = 0.0f;
			for (e = 0; e < 4; e++) {
				sum += mat1[e + row * 4] * mat2[col + e * 4];
			}
			res[col + row * 4] = sum;
		}
	}
}

void mat4_print(float mat[])
{
	int i, row, col;

	for (col = 0; col < 4; col++) {
		for (row = 0; row < 4; row++) {
			printf("%0.2f, ", mat[col + row * 4]);
		}
		printf("\n");
	}
}

