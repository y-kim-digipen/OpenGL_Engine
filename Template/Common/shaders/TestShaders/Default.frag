/*
 *  Doyoon Kim
 *  Graphic Class Project
 *  CS 250
 *  Spring 2021
 */

#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vClrCoord;
layout (location = 2) in vec3 vNormal;
uniform vec3 uDirectionalLight;

layout (location=0) out vec4 fFragClr;

void main () {
  float d = dot(uDirectionalLight , vNormal);
  fFragClr = vec4(vClrCoord * d, 1.0);
}
