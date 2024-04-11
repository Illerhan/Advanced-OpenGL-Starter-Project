#version 450 core

layout(vertices = 4) out;

uniform float ratioInner;
uniform float ratioOuter;
void main(void)
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = ratioOuter;
        gl_TessLevelInner[1] = ratioOuter;
        gl_TessLevelOuter[0] = ratioInner;
        gl_TessLevelOuter[1] = ratioInner;
        gl_TessLevelOuter[2] = ratioInner;
        gl_TessLevelOuter[3] = ratioInner
        ;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}