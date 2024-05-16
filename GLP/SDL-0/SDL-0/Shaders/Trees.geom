#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 9) out;

void main() {

    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();

    for(int i = 0; i < 3; i++) {
        vec3 v0 = gl_in[(i + 1) % 3].gl_Position.xyz - gl_in[i].gl_Position.xyz;
        vec3 v1 = gl_in[(i + 2) % 3].gl_Position.xyz - gl_in[i].gl_Position.xyz;
        vec3 normal = normalize(cross(v0, v1));

        gl_Position = gl_in[i].gl_Position;
        EmitVertex();

        gl_Position = gl_in[i].gl_Position + vec4(normal * 0.1, 0.0);
        EmitVertex();
    }
    EndPrimitive();
}