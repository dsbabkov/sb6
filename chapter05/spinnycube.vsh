#version 130

in vec4 position;

out vec4 vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
    gl_Position = proj_matrix * mv_matrix * position;
    vs_out = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}
