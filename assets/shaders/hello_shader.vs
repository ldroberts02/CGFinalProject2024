#version 330 core

in vec3 aPosition;
in vec2 aUV;

out vec2 fragmentUV;

void main()
{
    fragmentUV = aUV;
    gl_Position = vec4(vec3(aPosition), 1.0);
}