#version 460 core
out vec4 FragColor;
in vec2 uv;

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIterations;
uniform float u_time;

void main() {
    float rad = u_time/2.0;
    mat2 rot = mat2(cos(rad), -sin(rad), sin(rad), cos(rad));
    vec2 pos = uv * rot;

    vec2 rect = vec2(0.2, 0.2);
    vec2 abs_uv = abs(uv);
    float is_inside = step(abs_uv.x, rect.x) * step(abs_uv.y, rect.y);

    vec2 floored = floor(pos*5);
    float x = mod(floored.x+floored.y, 2) + is_inside;
    FragColor = vec4(x, x, x, 0.);
}
