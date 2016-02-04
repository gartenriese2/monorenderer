#version 450 core

layout(location = 0) out vec4 outColor;

layout(std430, binding = 0) restrict readonly buffer SSBO {
	vec4 color[];
};

uniform uint width;

void main() {
	vec2 coord = gl_FragCoord.xy;
	uint index = (uint(coord.y) - 1) * width + uint(coord.x);

	outColor = vec4(color[index]);
}
