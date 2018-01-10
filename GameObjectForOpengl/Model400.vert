#version 430  
  
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
  
out vec3 Position;  
out vec2 TextCoord;
out vec3 vNormal;
out vec3 Tangent;
out vec3 ShadowCoord;

uniform mat4 gl_ModelViewMatrix;  
uniform mat3 gl_NormalMatrix;  
uniform mat4 gl_ProjectionMatrix;  
uniform mat4 gl_ModelViewProjectionMatrix;
uniform mat4 shadowVP;
uniform mat4 viewReverseMat;
  
void main()  
{  
    Position = vec3(gl_ModelViewMatrix * vec4(position,1.0));  
	TextCoord = textCoord;

    vNormal = normalize(gl_NormalMatrix * normal);  
	Tangent = normalize(vec3(gl_ModelViewMatrix * vec4 (tangent,0)));
	vec3 scd = (shadowVP * viewReverseMat * gl_ModelViewMatrix * vec4(position,1)).xyz;
	ShadowCoord = scd * 0.5 + vec3(0.5,0.5,0.5);

    gl_Position = gl_ModelViewProjectionMatrix * vec4(position,1.0);  
}  