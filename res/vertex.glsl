#version 300 es

in vec3 vertexPosition;

void main() {
    gl_Position.xyz = vertexPosition;
    gl_Position.w = 1.f;
}