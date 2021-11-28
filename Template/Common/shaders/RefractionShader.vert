#version 450 core

uniform mat4 vertexTransform;
uniform mat4 vertexNormalTransform;

in layout(location = 0) vec3 vPosition;
in layout(location = 1) vec3 vertexNormal;


out VS_OUT
{
    vec3 vertexPosition;
    vec3 vertexNormal;
} vs_out;

void main() {
    vec4 Position = vertexTransform * vec4( vPosition, 1.0f );
    gl_Position = Position;
    vs_out.vertexPosition = (vertexNormalTransform * vec4( vPosition, 1.0f )).xyz;
    vs_out.vertexNormal = mat3(vertexNormalTransform) * vertexNormal;
//    vs_out.vertexPosition =  mat3(vertexNormalTransform) * vPosition;
}
