#version 330 core

out vec4 color;

in vec2 TexCoords;

uniform sampler2D sceneTexture;

void main()
{
	vec4 texColor = texture(sceneTexture, TexCoords);

    float brightness = dot(texColor.rgb, vec3(0.2126, 0.7152, 0.0722));

    if(brightness > 1.0)
        color = vec4(texColor.rgb, 1.0);
	else
		color = vec4(0.0, 0.0, 0.0, 1.0);
};