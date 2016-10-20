#version 430 core

out vec4 color;
uniform sampler2D image;

in vec3 N;
in vec3 L;
in vec3 V;
in vec2 UV;

void main(void)
{
    vec3 ambient = vec3(0.1745, 0.01175, 0.01175) * L;
    vec3 white = vec3(0.7278, 0.6270, 0.627);

    vec3 R = normalize(reflect(-L, N));

    float e = 76.8;
    float specular = pow( max( 0.0, dot(R, V)), e);

    vec3 gold = vec3(0.614, 0.0414, 0.0414);

    float diffuse = dot(N,L);
    float kd = 0.3;


    vec4 colorFromImage = texture(image, UV);
    vec4 ambientPart = colorFromImage * 0.9;
    vec4 diffusePart =  colorFromImage * diffuse;

    vec4 specularPart = colorFromImage * specular;
    color =   ambientPart + diffusePart + specularPart;


    //color = vec4( ambient + diffuse*gold + specular * white, 1.0);
}
