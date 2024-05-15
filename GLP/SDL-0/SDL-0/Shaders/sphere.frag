#version 330 core
in vec3 FragPos;            // Position of the fragment
in float DistanceToCenter;  // Distance from the center of the sphere

uniform vec3 SphereCenter;  // Center of the sphere

out vec4 FragColor;

void main()
{
    float contrast = 3;
    float maxDistance = length(vec3(1.0, 1.0, 1.0));  // Max distance from the center
    float normalizedDistance = DistanceToCenter / maxDistance;  // Normalize distance
    normalizedDistance = pow(normalizedDistance, contrast);
    // Calculate color based on distance
    vec3 color = mix(vec3(0.0,0.0,0.0), vec3(1.0,1.0,1.0),normalizedDistance);

    FragColor = vec4(color, 1.0);
}