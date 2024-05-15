#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main() {
    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();

    // Emit lines along the edges of the triangle
    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();

        gl_Position = gl_in[(i + 1) % 3].gl_Position;
        EmitVertex();
        EndPrimitive();
    }
}