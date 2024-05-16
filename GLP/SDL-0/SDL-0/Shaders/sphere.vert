#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform sampler2D noiseTexture;
uniform float noiseScale;
uniform float noiseStrength;

void main() {
    
    vec2 texCoord = vec2(aPos.x * noiseScale, aPos.y * noiseScale);
    float noiseValue = texture(noiseTexture, texCoord).r;
    
    vec3 displacedPos = aPos + normalize(aPos) * noiseValue * noiseStrength;

    gl_Position = projection * view * model * vec4(displacedPos, 1.0);
    
    FragPos = vec3(model * vec4(displacedPos, 1.0));
}