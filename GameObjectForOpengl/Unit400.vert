#version 430  
  
attribute vec4 gl_Vertex;
attribute vec4 gl_Color; 

out vec4 Color;

uniform mat4 gl_ModelViewProjectionMatrix;
  
void main()  
{  
	Color = gl_Color;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
}  