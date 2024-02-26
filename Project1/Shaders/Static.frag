
#version 330 core



in vec2 uv;
out vec4 FragColor;

uniform sampler2D sceneTexture;
uniform float intensity;
uniform float time;



void main() 
{
  
    vec4 originalColor = texture(sceneTexture, uv);  
    float randomNoise = fract(sin(dot(uv + time, vec2(11.718, 67.987))) * 43981.9372);
    float staticIntensity = intensity;

   
    vec4 finalColor = mix(originalColor, vec4(vec3(randomNoise), 1.0), staticIntensity);
    FragColor = finalColor;
}
