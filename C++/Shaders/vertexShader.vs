#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform float horizontalOffset;
uniform float verticalOffset;

out vec3 colorInput;

void main(){
	gl_Position = vec4(position.x + horizontalOffset, position.y + verticalOffset, position.z, 1.0f);
	colorInput = color;
}