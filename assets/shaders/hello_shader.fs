#version 330 core
//The fragment shader operates on each pixel in a given polygon
out vec4 FragColor;

uniform vec3 COLOR;

void main() {
	FragColor = vec4(vec3(color), 1.0);
}