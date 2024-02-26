#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform bool isEffectEnabled;

uniform sampler2D sceneTexture;
uniform sampler2D effectTexture;

void main()
{
    const float gamma = 2.2;

	vec3 hdrColor = texture(sceneTexture, TexCoords).rgb;
    vec3 effectColor = texture(effectTexture, TexCoords).rgb;

    if(isEffectEnabled)
    {
        hdrColor += effectColor;
    }

    color = vec4(hdrColor,1.0);
};