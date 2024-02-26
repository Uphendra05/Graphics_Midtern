#version 330 core
in vec2 uv;
out vec4 FragColor;

uniform sampler2D sceneTexture;
uniform float aberration;
uniform float time;

//void main() {
//    vec2 redUV = uv + aberration;
//    vec2 greenUV = uv;
//    vec2 blueUV = uv - aberration;
//
//    vec3 red = texture(sceneTexture, redUV).rgb;
//    vec3 green = texture(sceneTexture, greenUV).rgb;
//    vec3 blue = texture(sceneTexture, blueUV).rgb;
//    vec4 scene = texture(sceneTexture, uv);
//
//    FragColor = vec4(red, 1.0) + vec4(green, 1.0) + vec4(blue, 1.0);
//   // FragColor = scene;
//}

void main()
{
    vec2 uv1 = uv;

	//float aberration = 0.0;
	float value= aberration;
	value = (1.0 + sin(time*6.0)) * 0.5;
	value *= 1.0 + sin(time*16.0) * 0.5;
	value *= 1.0 + sin(time*19.0) * 0.5;
	value *= 1.0 + sin(time*27.0) * 0.5;
	value = pow(value, 3.0);

	value *= 0.05;
	
    vec3 col;
    col.r = texture( sceneTexture, vec2(uv1.x+value,uv1.y) ).r;
    col.g = texture( sceneTexture, uv ).g;
    col.b = texture( sceneTexture, vec2(uv1.x-value,uv1.y) ).b;

	col *= (1.0 - value * 0.5);
	
    FragColor = vec4(col,1.0);
}