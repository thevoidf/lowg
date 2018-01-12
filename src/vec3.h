#ifndef VEC4_H
#define VEC4_H

typedef struct {
	float x, y, z;
} vec3;

void vec3_add(vec3 *res, vec3 vec1, vec3 vec2);
void vec3_print(vec3 vec);

#endif
