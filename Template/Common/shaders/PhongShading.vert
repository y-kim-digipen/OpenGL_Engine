
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
    float NdotL;
    float RdotV;
    float S;
    float Att;
} shading_data;

uniform vec3 AmbientColor = vec3(1.f, 0.f, 0.f);

void main() {
    gl_Position = perspectiveMatrix * modelToWorldTransform * vec4(vPosition, 1.f);
    vec3 Position = (modelToWorldTransform * vec4(vPosition, 1.f)).xyz;
    vec3 Normal = mat3(modelToWorldTransform) *  vertexNormal;

    vec3 L = LightPos - Position;
    float LightDistance = length(L);
    vec3 L_Normalized = L / LightDistance;

    vec3 V = CameraPos - Position;
    float CameraDistance = length(V);
    vec3 V_Normalized = V / CameraDistance;

    //todo change this
    vec3 N = normalize(Normal);

    float NdotL = dot(N, L_Normalized);
    shading_data.NdotL = NdotL;

    vec3 ReflectionVector = 2 * NdotL * N - L_Normalized;

    float RdotV = dot(ReflectionVector, V_Normalized);
    shading_data.RdotV = RdotV;

    float Att = min(1.f/(c1 + c2 * LightDistance + c3 * LightDistance * LightDistance), 1.f);

    shading_data.Att = Att;

    float S = (zFar - CameraDistance)/(zFar - zNear);
    shading_data.S = S;
}
