#version 330 core
in vec3 pos;

uniform mat4 mv_matrix;
uniform mat4 projection;

out vec3 FragPos;  // Pass position to fragment shader
out float DistanceToCenter;  // Pass distance to fragment shader

float hash(vec3 p) {
    return fract(sin(dot(p, vec3(12.9898, 78.233, 151.7182))) * 43758.5453);
}

void main()
{
    vec3 noiseOffset = vec3(1.0, 2.0, 3.0);  // Adjust this vector to change the noise pattern
    float noiseValue = hash(pos + noiseOffset);
    vec3 displacedPos = pos + noiseValue * normalize(pos);  // Displace along the normal direction

    gl_Position = projection * mv_matrix * vec4(displacedPos, 1.0);
    FragPos = displacedPos;  // Pass displaced position to fragment shader
    DistanceToCenter = length(displacedPos);  // Calculate and pass distance to center of sphere
}