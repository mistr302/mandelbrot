#version 460 core
#ifdef GL_ES
precision mediump float;
#endif

// uniform vec2 u_resolution;
uniform float u_time;
uniform vec3 u_zoom;
in vec2 uv;
out vec4 FragColor;
void main() {
    // Adjust aspect ratio
    // uv.x *= u_resolution.x / u_resolution.y;

    // float rad = u_time/2.0;
    // mat2 rot = mat2(cos(rad), -sin(rad), sin(rad), cos(rad));
    // vec2 pos = uv * rot;
    
    vec2 c = (uv+u_zoom.xy)/u_zoom.z;      // constant per pixel
    // vec2 c = uv;      // constant per pixel
    vec2 z = vec2(0.0); // start at 0 for Mandelbrot

    int maxIter = 100;
    int i;

    for (i = 0; i < maxIter; i++) {
        // z = z² + c
        z = vec2(
            z.x*z.x - z.y*z.y,
            2.0*z.x*z.y
        ) + c;

        // Escape condition (|z| > 2)
        if (dot(z, z) > 4.0) break;
    }

    float color = float(i) / float(maxIter);
    FragColor = vec4(vec3(color), 1.0);
}
