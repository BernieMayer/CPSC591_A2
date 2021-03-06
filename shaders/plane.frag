#version 430 core

out vec4 color;

uniform sampler1D colormap;
uniform sampler2D image;

in vec3 N;
in vec3 P;
in vec3 L;
in vec2 UV;

void main (void)
{
    vec3 diffuse_albedo = vec3(1.0, 1.0, 1.0);
    float kd = 0.8;

    vec4 colorFromImage = texture(image, UV);

    float diffuse = max(0.0, dot(N, normalize(L - P)));
    //vec4 C = texture( colormap, diffuse);

    color = colorFromImage;
    //color = C;
}
