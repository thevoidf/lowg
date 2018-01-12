#include <math.h>
#include "mat4.h"

float to_radians(float deg)
{
	return (float) (deg * (M_PI / 180.0f));
}

void normalize(float elements[])
{
	int i;
	for (i = 0; i < 4*4; i++)
		elements[i] = 0.0f;

	elements[0 + 0 * 4] = 1.0f;
	elements[1 + 1 * 4] = 1.0f;
	elements[2 + 2 * 4] = 1.0f;
	elements[3 + 3 * 4] = 1.0f;
}

void
proj(float elements[],
		float fov,
		float aspect_ratio,
		float near,
		float far)
{
	normalize(elements);

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
translate(float elements[], float x, float y, float z)
{
	normalize(elements);

	elements[0 + 3 * 4] = x;
	elements[1 + 3 * 4] = y;
	elements[2 + 3 * 4] = z;
}
