#version 430  
  
attribute vec4 gl_Vertex;
attribute vec3 gl_Normal;
attribute vec4 gl_Color; 

out vec3 Position;  
out vec3 vNormal;
out vec4 Color;
out vec3 ShadowCoord;

uniform mat4 gl_ModelViewMatrix;  
uniform mat3 gl_NormalMatrix;  
uniform mat4 gl_ProjectionMatrix;  
uniform mat4 gl_ModelViewProjectionMatrix;
uniform mat4 shadowVP;
uniform mat4 viewReverseMat;
  
void main()  
{  
    Position = vec3(gl_ModelViewMatrix * gl_Vertex);  
    vNormal = normalize(gl_NormalMatrix * gl_Normal);  
	Color = gl_Color;
	vec3 scd = (shadowVP * viewReverseMat * gl_ModelViewMatrix * gl_Vertex).xyz;
	ShadowCoord = scd * 0.5 + vec3(0.5,0.5,0.5);

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
}  