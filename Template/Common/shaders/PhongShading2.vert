
#version 420 core

uniform mat4 modelToWorldTransform;
uniform mat4 perspectiveMatrix;

in layout(location = 0) vec3 vPosition;
in layout(location = 1) vec3 vertexNormal;

uniform vec3 LightPos = vec3(0.f, 0.f, -4.f);
uniform vec3 CameraPos;

//Environment
float zNear = 0.1, zFar = 50;
uniform float c1 = 0.7, c2 = 0.4, c3 = 0.2;

out  PhongShadingData
{
    vec3 Position;
    vec3 Normal;
} shading_data;

uniform vec3 AmbientColor = vec3(1.f, 0.f, 0.f);

void main() {
    gl_Position = perspectiveMatrix * modelToWorldTransform * vec4(vPosition, 1.f);
    vec3 Position = (modelToWorldTransform * vec4(vPosition, 1.f)).xyz;
    vec3 Normal = mat3(modelToWorldTransform) *  vertexNormal;

    shading_data.Position = Position;
    shading_data.Normal = Normal;
}
