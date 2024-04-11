#version 450 core


layout (vertices = 3) out;

uniform float ratioOuter;
uniform float ratioInner;

void main(void)
{
    if(gl_InvocationID == 0) {
        gl_TessLevelInner[0] = ratioInner;
        gl_TessLevelOuter[0] = ratioOuter;
        gl_TessLevelOuter[1] = ratioOuter;
        gl_TessLevelOuter[2] = ratioOuter;
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
