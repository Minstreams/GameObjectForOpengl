#version 430  
  
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
  
attribute vec4 gl_Color; 

out vec3 Position;  
out vec2 TextCoord;
out vec3 vNormal;
out vec3 Tangent;

uniform mat4 gl_ModelViewMatrix;  
uniform mat3 gl_NormalMatrix;  
uniform mat4 gl_ProjectionMatrix;  
uniform mat4 gl_ModelViewProjectionMatrix;
  
void main()  
{  
    Position = vec3(gl_ModelViewMatrix * vec4(position,1.0));  
	TextCoord = textCoord;

    vNormal = normalize(gl_NormalMatrix * normal);  
	Tangent = normalize(vec3(gl_ModelViewMatrix * vec4 (tangent,0)));

    gl_Position = gl_ModelViewProjectionMatrix * vec4(position,1.0);  
}  