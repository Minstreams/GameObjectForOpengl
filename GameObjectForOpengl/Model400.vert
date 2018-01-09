#version 430  
  
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 normal;
  
out vec3 Position;  
out vec3 Normal;  
out vec2 TextCoord;

uniform mat4 gl_ModelViewMatrix;  
uniform mat3 gl_NormalMatrix;  
uniform mat4 gl_ProjectionMatrix;  
uniform mat4 gl_ModelViewProjectionMatrix;

uniform mat4 modelScale;
  
void main()  
{  
    Position = vec3(gl_ModelViewMatrix * vec4(position,1.0));  
    Normal = normalize(gl_NormalMatrix * normal);  
	TextCoord = textCoord;

    gl_Position = gl_ModelViewProjectionMatrix * modelScale * vec4(position,1.0);  
}  