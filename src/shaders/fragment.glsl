#version 330 core
out vec4 FragColor;
in vec2 uv;

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIterations;
uniform float u_time;

void main() {
    float dist = length(uv);
    float sined = sin(dist * 8. - u_time)/2.;
    float final = abs(sined);
    final = step(.2,final);
    // final = 0.01 / final;
    FragColor = vec4(sin(final), 1., 1., 0.);
}
