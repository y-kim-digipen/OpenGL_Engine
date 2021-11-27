#version 450 core

layout (binding = 0) uniform sampler2D rightDiffuseBuffer;
layout (binding = 1) uniform sampler2D leftDiffuseBuffer;
layout (binding = 2) uniform sampler2D topDiffuseBuffer;
layout (binding = 3) uniform sampler2D bottomDiffuseBuffer;
layout (binding = 4) uniform sampler2D frontDiffuseBuffer;
layout (binding = 5) uniform sampler2D backDiffuseBuffer;

uniform vec3 CameraPos_GUIX;

uniform float eta = 1.f / 1.002;

in VS_OUT
{
    vec3 vertexPosition;
    vec3 vertexNormal;
} fs_in;

out vec3 Color;

void main() {
    vec3 I = -normalize(fs_in.vertexPosition/* - CameraPos_GUIX*/);
    vec3 N = normalize(fs_in.vertexNormal);

    vec3 T = vec3(0.f);
    float NdotI = dot(N, I);
    float K = 1.f - eta * eta * (1.f - NdotI * NdotI);
    (K < 0.f) ? (T = vec3(0.f)): (T = eta * I - (eta * NdotI + sqrt(K)) * N);
    vec3 vEntity = normalize(T);
    vec3 absVec = abs(vEntity);
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
//    else
//    {
//        plane = -1;
//    }
    //    uv.y = -uv.y;
    uv = (uv + vec2(1.f)) * 0.5f;

    vec3 FinalColor = vec3(0.f);

    switch (plane)
    {
        case -1:
        {
FinalColor = vec3(1.f, 0.f, 0.f);
            break;
        }
        case 0:
        {
            FinalColor = texture(rightDiffuseBuffer, uv).rgb;
            //            FinalColor = vec3(1.f, 0.f, 0.f); //r
            break;
        }
        case 1:
        {
            FinalColor = texture(leftDiffuseBuffer, uv).rgb;
            //            FinalColor = vec3(0.f, 1.f, 0.f); //g
            break;
        }
        case 2:
        {
            FinalColor = texture(topDiffuseBuffer, uv).rgb;
            //            FinalColor = vec3(0.f, 0.f, 1.f); //b
            break;
        }
        case 3:
        {
            FinalColor = texture(bottomDiffuseBuffer, uv).rgb;
            //            FinalColor = vec3(1.f, 1.f, 0.f); //yellow
            break;
        }
        case 4:
        {
            FinalColor = texture(frontDiffuseBuffer, uv).rgb;
             //          FinalColor = vec3(1.f, 0.f, 1.f); //pink
            break;
        }
        case 5:
        {
            FinalColor = texture(backDiffuseBuffer, uv).rgb;
            //           FinalColor = vec3(0.f, 1.f, 1.f); //cyan
            break;
        }
    }

    Color = FinalColor;

//    Color = normalize(V);
}
