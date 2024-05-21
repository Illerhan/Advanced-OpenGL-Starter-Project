#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;
out float DistanceToCenter;
void main() {

//    for(int i = 0; i < 3; i++) {
//        gl_Position = gl_in[i].gl_Position;
//        EmitVertex();
//    }
//    EndPrimitive();

vec4 center = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
DistanceToCenter = 0;        
vec3 v0 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
vec3 v1 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
vec3 normal = normalize(cross(v0, v1));

vec4 endpoint = center + vec4(normal * -0.5, 0.0);
    
gl_Position = center;
EmitVertex();

gl_Position = endpoint;
EmitVertex();
//    for(int i = 0; i < 3; i++) {
//        vec3 v0 = gl_in[(i + 1) % 3].gl_Position.xyz - gl_in[i].gl_Position.xyz;
//        vec3 v1 = gl_in[(i + 2) % 3].gl_Position.xyz - gl_in[i].gl_Position.xyz;
//        vec3 normal = normalize(cross(v0, v1));
//
//        gl_Position = gl_in[i].gl_Position;
//        EmitVertex();
//
//        gl_Position = gl_in[i].gl_Position + vec4(normal * 0.1, 0.0);
//        EmitVertex();
//    }
    EndPrimitive();
}