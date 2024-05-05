uniform mat4 mv_matrix; // Use the same name as in the vertex shader
uniform mat4 projection;

layout(triangles) in;
layout(line_strip, max_vertices = 2) out;

void main()
{
    // Calculate face normal (assuming counter-clockwise winding order)
    vec3 edge1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 edge2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 faceNormal = normalize(cross(edge1, edge2));

    // Check if the face is flat (close to the normal of the sphere)
    float threshold = 0.95; // Adjust as needed
    float dotProduct = dot(faceNormal, vec3(0.0, 0.0, 1.0)); // Assuming normal of the sphere is (0, 0, 1)

    if (dotProduct > threshold)
    {
        // Calculate tree position along the displaced face normal
        vec3 treePosition = gl_in[0].gl_Position.xyz + faceNormal * 0.1; // Adjust displacement factor as needed

        // Transform tree position to clip space using the combined model-view matrix
        gl_Position = projection * mv_matrix * vec4(treePosition, 1.0);
        EmitVertex();

        // Emit a second vertex to form a line strip
        gl_Position = gl_in[0].gl_Position;
        EmitVertex();
    }

    EndPrimitive(); // Move EndPrimitive outside the if block
}