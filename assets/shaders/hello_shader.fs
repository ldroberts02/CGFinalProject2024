#version 330 core
//The fragment shader operates on each pixel in a given polygon
out vec4 FragColor;

in vec3 vertexColor;

void main() {
	FragColor = vec4(vec3(vertexColor), 1.0);
}