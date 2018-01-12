#ifndef MAT4_H
#define MAT4_H

#define M_PI 3.14159265358979323846

float to_radians(float deg);

void normalize(float elements[]);

void
proj(float elements[],
		float fov,
		float aspect_ratio,
		float near,
		float far);

void
translate(float elements[], float x, float y, float z);

#endif