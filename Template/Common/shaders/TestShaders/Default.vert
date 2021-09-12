/*
 *  Doyoon Kim
 *  Graphic Class Project
 *  CS 250
 *  Spring 2021
 */

#version 450 core

layout (location=0) in vec3 vVertexPosition;
layout (location=1) in vec3 vVertexNormal;
layout (location=2) in vec2 vVertexTexCoord;
uniform mat4 uMvpMatrix; 

layout (location = 0) out vec4 vPosition;
layout (location = 1) out vec3 vClrCoord;
layout (location = 2) out vec3 vNormal;

void main() 
{
  gl_Position = uMvpMatrix * vec4(vVertexPosition, 1.0);
  vPosition = gl_Position;
  vClrCoord = vVertexNormal;
  vNormal = vVertexNormal;
}
