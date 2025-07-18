#version 330 core
in vec3 FragPos;
in vec3 Normal;

layout(location = 0) out vec4 gPositionOut;
layout(location = 1) out vec4 gNormalOut;
layout(location = 2) out vec4 gAlbedoSpecOut;

uniform vec3 uColor;

void main() {
    gPositionOut = vec4(FragPos, 1.0); // World space position
    gNormalOut = vec4(normalize(Normal), 1.0); // Normalized normal
    gAlbedoSpecOut = vec4(uColor, 1.0); // Pure albedo (no light dir)
}