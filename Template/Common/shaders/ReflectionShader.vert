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

    gl_Position = vertexTransform * vec4( vPosition, 1.0f );
    vs_out.vertexPosition = (vertexTransform * vec4( vPosition, 1.0f )).xyz / (vertexTransform * vec4( vPosition, 1.0f )).w;
    vs_out.vertexNormal = mat3(vertexNormalTransform) * vertexNormal;
}
