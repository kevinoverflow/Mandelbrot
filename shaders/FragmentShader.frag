#version 330 core

precision highp float;

layout(location = 0) out vec4 color;
uniform float iterations;
uniform vec2 resolution;
uniform vec2 offset;
uniform float zoom;

float mandelbrot(vec2 c) {
  vec2 z = c;
  float i = 0.0;
  for (i = 0.0; i < iterations; i++) {
    z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
    if (length(z) > 2.0) break;
  }
  return i;
}

void main() {
  vec2 uv = (((gl_FragCoord.xy) - 0.5 * resolution.xy) / resolution.y) * zoom;

  float i = mandelbrot(uv + offset);

  vec3 col = vec3(0.0, 0.0, 0.0);
  col.xyz += i / iterations;
  color = vec4(col, 1.0);
}