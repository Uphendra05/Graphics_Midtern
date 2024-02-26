#version 330 core
in vec2 uv;
out vec4 FragColor;

uniform sampler2D sceneTexture;
uniform float effectAmount;
uniform float time;



void main()
{
    vec2 uv1 = uv;

	float value = effectAmount;
	value =  1.0 + sin(time * 1.0) * 0.7;
	value *= 1.0 + sin(time * 7.0) * 0.7;
	value *= 1.0 + sin(time * 17.0) * 0.7;
	value *= 1.0 + sin(time * 25.0) * 0.7;
	value = pow(value, 3.0);

    vec3 col;
    col.r = texture( sceneTexture, vec2(uv1.x+value,uv1.y) ).r;
    col.g = texture( sceneTexture, uv ).g;
    col.b = texture( sceneTexture, vec2(uv1.x-value,uv1.y) ).b;

	col *= (1.0 - value * 0.5);
	
    FragColor = vec4(col,1.0);
}