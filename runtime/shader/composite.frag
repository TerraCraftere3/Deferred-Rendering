#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal   = normalize(texture(gNormal, TexCoords).rgb);
    vec3 Albedo   = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    vec3 lightDir = normalize(vec3(-0.5, -1.0, 0.3));
    vec3 lightColor = vec3(1.0);

    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 ambient = vec3(0.1);

    vec3 lighting = (ambient + diffuse) * Albedo;

    FragColor = vec4(lighting, 1.0);
}
