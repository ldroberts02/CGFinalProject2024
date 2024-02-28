#version 330 core

in vec3 aPosition;
in vec2 aUV;

out vec2 fragmentUV;

uniform mat4 TRANSFORM;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

void main()
{
    fragmentUV = aUV;
    gl_Position = PROJECTION * VIEW * TRANSFORM * vec4(vec3(aPosition), 1.0);
}