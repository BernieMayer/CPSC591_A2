#version 430 core

out vec4 color;
uniform sampler2D image;
uniform float r;

in vec3 N;
in vec3 L;
in vec3 V;
in vec2 UV;

void main(void)
{
    vec3 ambient = vec3(0.1745, 0.01175, 0.01175) * L;
    vec3 white = vec3(0.7278, 0.6270, 0.627);

    vec3 R = normalize(reflect(-L, N));

    float e = 30;
    float specular = pow( max( 0.0, dot(R, V)), e);

    vec3 gold = vec3(0.614, 0.0414, 0.0414);
    vec3 violet = vec3(0.933, 0.5098, 0.9333);

    float diffuse = dot(N,L);
    float kd = 0.3;

    float D =  pow( abs(dot(N,V)), r);
    float lambertian = dot(N,L);
    if (lambertian < 0)
    {
       lambertian = 0.1;
    }
    vec2 uv = vec2( lambertian, D);
    vec4 colorFromImage = texture(image, uv);
    vec4 ambientPart = colorFromImage * 0.9;
    //vec4 diffusePart =  violet * diffuse;

    vec4 specularPart = colorFromImage * specular;
    color =  colorFromImage;
    //color = diffusePart;

    //color = vec4( ambient + diffuse * violet + specular * white, 1.0);
}
