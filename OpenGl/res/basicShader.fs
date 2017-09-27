#version 120

uniform sampler2D diffuse;

//varing shares stuff between shaders
varying vec2 texCoord0;
varying vec3 normal0;

void main()
{
gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(-vec3(0,0,1),normal0),0.0,1.0);

//Shader Colouring
//gl_FragColor = vec4(gl_FragCoord.x, gl_FragCoord.y, gl_FragCoord.z, 0.5);
//gl_FragColor = vec4(1.0,0.5,0.3,0.5);
}