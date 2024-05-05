#version 330 core
in vec3 pos;

uniform mat4 mv_matrix;
uniform mat4 projection;

out vec3 OurColor;

void main()
{
    gl_Position =  projection * mv_matrix * vec4(pos, 1.0);
    OurColor = vec3(1.0);
}