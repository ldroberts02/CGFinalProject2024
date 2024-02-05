#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 oNormal;
out vec2 texCoord;
out vec3 fragPos;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    oNormal = normalize(mat3(transpose(inverse(transform))) * aNormal);
    fragPos = vec3(transform * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(fragPos, 1.0);
    texCoord = aTexCoord;
}