#version 330 core

in vec3 aPosition;

out vec3 vertexColor;

void main()
{
    vertexColor = aPosition;
    gl_Position = vec4(vec3(aPosition), 1.0);
}