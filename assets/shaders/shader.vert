#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform vec3 dir;
uniform mat4 transform;

void main()
{
  gl_Position = vec4(aPos.x + dir.x, aPos.y + dir.y, aPos.z, 1.0);
  ourColor = aColor;
}
