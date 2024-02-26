
#version 330 core



in vec2 uv;
out vec4 FragColor;

uniform sampler2D sceneTexture;
uniform float time;



void main() 
{
  
    vec4 originalColor = texture(sceneTexture, uv);  
    float randomNoise = fract(sin(dot(uv + time, vec2(12.9898, 78.233))) * 43758.5453); 
    float staticIntensity = 0.5;

   
    vec4 finalColor = mix(originalColor, vec4(vec3(randomNoise), 1.0), staticIntensity);
    FragColor = finalColor;
}
