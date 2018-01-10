#version 430  
  
attribute vec4 gl_MultiTexCoord0; 
attribute vec4 gl_Vertex;
attribute vec3 gl_Normal;
attribute vec4 gl_Color; 

out vec4 Color;
out vec3 Position;  
out vec2 TextCoord;
out vec3 Normal;
out vec3 ShadowCoord;

uniform mat4 gl_ModelViewMatrix;  
uniform mat3 gl_NormalMatrix;  
uniform mat4 gl_ProjectionMatrix;  
uniform mat4 gl_ModelViewProjectionMatrix;
uniform mat4 gl_TextureMatrix[1];
uniform mat4 shadowVP;
uniform mat4 viewReverseMat;
  
void main()  
{  
	Color = gl_Color;
    Position = vec3(gl_ModelViewMatrix * gl_Vertex);  
	TextCoord = (gl_TextureMatrix[0]*gl_MultiTexCoord0).xy;
    Normal = normalize(gl_NormalMatrix * gl_Normal);  
	vec3 scd = (shadowVP * viewReverseMat * gl_ModelViewMatrix * gl_Vertex).xyz;
	ShadowCoord = scd * 0.5 + vec3(0.5,0.5,0.5);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
}  