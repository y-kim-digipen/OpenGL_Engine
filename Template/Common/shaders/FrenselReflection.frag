#version 450 core

layout (binding = 0) uniform sampler2D rightDiffuseBuffer;
layout (binding = 1) uniform sampler2D leftDiffuseBuffer;
layout (binding = 2) uniform sampler2D topDiffuseBuffer;
layout (binding = 3) uniform sampler2D bottomDiffuseBuffer;
layout (binding = 4) uniform sampler2D frontDiffuseBuffer;
layout (binding = 5) uniform sampler2D backDiffuseBuffer;

uniform vec3 CameraPos_GUIX;

uniform float Eta = 0.89;

uniform float EtoR = 0.85;
uniform float EtoG = 0.87;
uniform float EtoB = 0.89;

in VS_OUT
{
    vec3 vertexPosition;
    vec3 vertexNormal;
} fs_in;

out vec3 Color;

vec3 GetReflectionVector(vec3 I, vec3 N)
{
    return I - 2 * dot(I, N) * N;
}

vec3 GetRefractionVector(vec3 I, vec3 N, float eta)
{
    vec3 T = vec3(0.f);
    float NdotI = dot(N, I);
    float K = 1.f - eta * eta * (1.f - NdotI * NdotI);
    (K < 0.f) ? (T = vec3(0.f)): (T = eta * I - (eta * NdotI + sqrt(K)) * N);
    return T;
}

vec3 GetMappedColor(vec3 vEntity)
{
    vec3 absVec = abs(normalize(vEntity));
    vec2 uv = vec2(0.f);
    int plane;
    if (absVec.x >= absVec.y && absVec.x >= absVec.z)//abs x is biggest
    {
        (vEntity.x < 0.f) ? (uv.x = -vEntity.z, plane = 1) : (uv.x = vEntity.z, plane = 0);
        uv.y = vEntity.y;
        uv = uv / absVec.x;
    }
    else if (absVec.y >= absVec.x && absVec.y >= absVec.z)//abs y is biggest
    {
        (vEntity.y < 0.f) ? (uv.x = vEntity.x, plane = 3, uv.y = -vEntity.z) : (uv.x = vEntity.x, plane = 2, uv.y = vEntity.z);

        uv = uv / absVec.y;
    }
    else //abs z is biggest
    {
        (vEntity.z < 0.f) ? (uv.x = vEntity.x, plane = 5) : (uv.x = -vEntity.x, plane = 4);
        uv.y = vEntity.y;

        uv = uv / absVec.z;
    }
    //    uv.y = -uv.y;
    uv = (uv + vec2(1.f)) * 0.5f;

    vec3 FinalColor = vec3(0.f);

    switch (plane)
    {
        case -1:
        {
            break;
        }
        case 0:
        {
            FinalColor = texture(rightDiffuseBuffer, uv).rgb;
            break;
        }
        case 1:
        {
            FinalColor = texture(leftDiffuseBuffer, uv).rgb;
            break;
        }
        case 2:
        {
            FinalColor = texture(topDiffuseBuffer, uv).rgb;
            break;
        }
        case 3:
        {
            FinalColor = texture(bottomDiffuseBuffer, uv).rgb;
            break;
        }
        case 4:
        {
            FinalColor = texture(frontDiffuseBuffer, uv).rgb;
            break;
        }
        case 5:
        {
            FinalColor = texture(backDiffuseBuffer, uv).rgb;
            break;
        }
    }
    return FinalColor;
}

void main() {
    vec3 V = normalize(fs_in.vertexPosition - CameraPos_GUIX);
    vec3 N = normalize(fs_in.vertexNormal);

//    float f = ((1.f - Eta) * (1.f - Eta)) / ((1.f + Eta) * (1.f + Eta));
    float f = ((1.f - EtoG) * (1.f - EtoG)) / ((1.f + EtoG) * (1.f + EtoG));
    float Ratio = f + (1.f - f) * pow((1.f - dot(-V, N)), 5);


    vec3 ReflectionVector = GetReflectionVector(V, N);
//    vec3 RefractionVector = GetRefractionVector(V, N, Eta);
    vec3 RefractionVectorR = GetRefractionVector(V, N, EtoR);
    vec3 RefractionVectorG = GetRefractionVector(V, N, EtoG);
    vec3 RefractionVectorB = GetRefractionVector(V, N, EtoB);

    vec3 ReflectionColor = GetMappedColor(ReflectionVector);
//    vec3 RefractionColor = GetMappedColor(RefractionVector);
    float RefractionColorR = GetMappedColor(RefractionVectorR).r;
    float RefractionColorG = GetMappedColor(RefractionVectorG).g;
    float RefractionColorB = GetMappedColor(RefractionVectorB).b;
    vec3 RefractionColor = vec3(RefractionColorR, RefractionColorG, RefractionColorB);
    vec3 FinalColor = mix(RefractionColor, ReflectionColor, Ratio);
//    vec3 FinalColor = RefractionColor;

    Color = FinalColor;
}
