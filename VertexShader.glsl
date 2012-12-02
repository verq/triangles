#version 120

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexBaricentric;

uniform float scale;
smooth out vec3 fragmentColor;


void main() {	

	gl_Position = vec4(vertexPosition.x * scale, vertexPosition.y * scale, vertexPosition.z * scale, 1);
	fragmentColor = vertexBaricentric;
}




