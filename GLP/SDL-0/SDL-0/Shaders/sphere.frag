#version 330 core
in vec3 FragPos;           
in float DistanceToCenter; 

uniform vec3 SphereCenter;

out vec4 FragColor;

void main()
{
    float contrast = 4;
    float maxDistance = length(vec3(1.0, 1.0, 1.0));
    float normalizedDistance = DistanceToCenter / maxDistance;
    normalizedDistance = pow(normalizedDistance, contrast);
    vec3 color = mix(vec3(0.0,0.5,1.0), vec3(0.5,1.0,0.0),normalizedDistance);
    FragColor = vec4(color, 1.0);
}