#version 420 core
#define MAX_NUM_TOTAL_LIGHTS 10
uniform int NumActiveLights = 1;
uniform vec3 CameraPos;

//Environment
float zNear = 1, zFar = 40;
uniform float c1 = 0.7, c2 = 0.4, c3 = 0.2;
uniform vec3 I_Fog = vec3(0.3f);

uniform LightArray
{
////Light
//    vec3 Pos = vec3(0.f, 0.f, -4.f);
//
////material
//    float Ka = 0.1f;
//    float Kd = 0.5f;
//    float Ks = 0.80f;
//    vec3 I_Emissive = vec3(50, 10, 10) ;
//    float ns = 3.f;
//
////Light
//    vec3 Ia = vec3(100, 100, 100) ;
//    vec3 Id = vec3(120, 250, 10) ;
//    vec3 Is = vec3(200, 200, 200) ;
//Light
    vec3 Pos;

//material
    float Ka;
    float Kd;
    float Ks;
    vec3 I_Emissive;
    float ns;

//Light
    vec3 Ia;
    vec3 Id;
    vec3 Is;
} LA[MAX_NUM_TOTAL_LIGHTS];

in PhongShadingData
{
    vec3 Position;
    vec3 Normal;
} shading_data;
out vec3 color;

void main() {
    vec3 Sum_Local_Light = vec3(0.f);

    vec3 V = CameraPos - shading_data.Position;
    float CameraDistance = length(V);
    vec3 V_Normalized = V / CameraDistance;
    for(int i = 0; i < NumActiveLights; ++i)
    {
        //Light
        vec3 Pos = LA[i].Pos;

        //material
        float Ka = LA[i].Ka;
        float Kd = LA[i].Kd;
        float Ks = LA[i].Ks;
        vec3 I_Emissive = LA[i].I_Emissive;
        float ns = LA[i].ns;

        //Light
        vec3 Ia = LA[i].Ia;
        vec3 Id = LA[i].Id;
        vec3 Is = LA[i].Is;

        vec3 L = Pos - shading_data.Position;
        //    vec3 L = vec3(1.f, 0.f, 0.f);
        float LightDistance = length(L);
        vec3 L_Normalized = L / LightDistance;

        vec3 N = normalize(shading_data.Normal);

        float NdotL = dot(N, L_Normalized);
        vec3 ReflectionVector = 2 * NdotL * N - L_Normalized;
        float RdotV = dot(ReflectionVector, V_Normalized);
        float Att = min(1.f/(c1 + c2 * LightDistance + c3 * LightDistance * LightDistance), 1.f);


        vec3 I_Ambient = Ia * Ka;
        float diffuse_comp = max(NdotL, 0.f);
        vec3 I_Diffuse = Id * Kd * diffuse_comp;
        vec3 I_Specular = Is * Ks * pow(diffuse_comp > 0.f ? max(RdotV, 0.f) : 0.f, ns);

        //    Att = 1.f;
        Sum_Local_Light += I_Emissive + Att * (I_Ambient + I_Diffuse + I_Specular);
    }
    float S = (zFar - CameraDistance)/(zFar - zNear);
    vec3 I_Local = Sum_Local_Light / NumActiveLights;
    vec3 I_Fianl = S * I_Local + (1.f - S) * I_Fog;
    color = I_Fianl / vec3(256.f);
}
