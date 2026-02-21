#version 330 core
out vec4 FragColor;
in vec2 uv;

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIterations;
uniform float u_time;

void main() {
    vec2 floored = floor(uv*5);
    float x = mod(floored.x+floored.y, 2);
    FragColor = vec4(x, x, x, 0.);
}
