#include <stdio.h>
#include "vec3.h"

void vec3_add(vec3 *res, vec3 vec1, vec3 vec2)
{
	res->x = vec1.x + vec2.x;
	res->y = vec1.y + vec2.y;
	res->z = vec1.z + vec2.z;
}

void vec3_print(vec3 vec)
{
	printf("{x: %.2f, y: %.2f, z: %.2f}\n",
					vec.x, vec.y, vec.z);
}
