#version 330 core

in vec2 TexCoord;

out vec2 TexCoord;


void main()
{
    vec4 offset = vec4(float(gl_InstanceID>>10)-512.0,0.0f,float(gl_InstanceID&0x3FF)-512.0,0.0f);
    vec2 TexCoord = offset.xz / 1024.0 + vec2(0.5);
    int number1 = random(gl_InstanceID,3);
    int number2 = random(number1,2);
    float bend_factor = texture(bend_texture, TexCoord).r * 2.0;
    float bend_amount = cos(vVertex.y);
    vec2 TexCoord_angle = TexCoord + time * 0.05;
    float angle = texture(orientation_texture,TexCoord_angle).r * 2.0 * 3.141595;
    mat4 rot = construct_rotation_matrix(angle);
    vec4 position = (rot*(vVertex + vec4(0.0,0.0, bend_amount + bend_factor,0.0)))+ offset;
    
    
    offset += vec4(float(number1 & 0xFF) / 256.0, 0.0f, float(number2 & 0xFF) / 256.0, 0.0f);
    position *= vec4(1.0,texture(length_texture, TexCoord).r*0.9+0.3);
    gl_Position = mvp_matrix * position;
    color = texture(grasspalette_texture(grasscolor_texture,TexCoord).r)+
            vec4(random_vector(gl_InstanceID).xyz * vec3(0.1,0.5,0.1),1.0);
}

