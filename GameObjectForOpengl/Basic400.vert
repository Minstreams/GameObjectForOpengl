#version 430  
  
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
  
attribute vec4 gl_Color; 

out vec3 Position;  
out vec3 vNormal;
out vec4 Color;

uniform mat4 gl_ModelViewMatrix;  
uniform mat3 gl_NormalMatrix;  
uniform mat4 gl_ProjectionMatrix;  
uniform mat4 gl_ModelViewProjectionMatrix;
  
void main()  
{  
    Position = vec3(gl_ModelViewMatrix * vec4(position,1.0));  
    vNormal = normalize(gl_NormalMatrix * normal);  
	Color = gl_Color;

    gl_Position = gl_ModelViewProjectionMatrix * vec4(position,1.0);  
}  