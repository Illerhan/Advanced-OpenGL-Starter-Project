#version 330 core
in vec3 pos;

uniform mat4 mv_matrix;
uniform mat4 projection;

out vec3 FragPos;
out float DistanceToCenter;

float hash(vec3 p) {
    return fract(sin(dot(p, vec3(10, 78.233, 75))) * 43758.5453);
}

void main()
{
    vec3 noiseOffset = vec3(4.0,2.0, 100.f); 
    float noiseValue = hash(pos + noiseOffset);
    vec3 displacedPos = pos + noiseValue * normalize(pos); 

    gl_Position = projection * mv_matrix * vec4(displacedPos, 1.0);
    FragPos = displacedPos;
    DistanceToCenter = length(displacedPos); 
}