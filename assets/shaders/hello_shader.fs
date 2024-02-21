#version 330 core
//The fragment shader operates on each pixel in a given polygon
out vec4 FragColor;

in vec2 fragmentUV;

uniform vec3 COLOR;
uniform sampler2D MEMETEXTURE;

void main() {
	FragColor = texture(MEMETEXTURE, fragmentUV);
}