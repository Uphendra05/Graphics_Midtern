#version 330 core
in vec2 uv;
out vec4 FragColor;

uniform sampler2D sceneTexture;
uniform float aberration;
uniform float time;


void main()
{
    vec2 uv1 = uv;

	float value= aberration;
	value = (1.0 + sin(time*6.0)) * 0.5;	
	value *= 1.0 + sin(time*27.0) * 0.5;
	value = pow(value, 3.0);

	
    vec3 col;
    col.r = texture( sceneTexture, vec2(uv1.x+value,uv1.y) ).r;
    col.g = texture( sceneTexture, uv ).g;
    col.b = texture( sceneTexture, vec2(uv1.x-value,uv1.y) ).b;

	col *= (1.0 - value * 0.5);
	
    FragColor = vec4(col,1.0);
}