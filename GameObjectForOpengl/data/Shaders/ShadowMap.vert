#version 430

attribute vec4 gl_Vertex;

uniform mat4 shadowVP;
uniform mat4 gl_ModelViewMatrix;  

void main()
{
    gl_Position =  shadowVP * gl_ModelViewMatrix * gl_Vertex;
}