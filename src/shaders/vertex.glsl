#version 330 core

out vec2 fragPos;

const vec2 vertices[3] = {
    {-1., -1.},
    {-1., +3.},
    {+3., -1.},
};

void main() {
    gl_Position = vec4(vertices[gl_VertexID], 0., 1.);
    fragPos = vertices[gl_VertexID];
}
