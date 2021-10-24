#version 420 core

#define MAX_NUM_TOTAL_LIGHTS 10
uniform vec3 CameraPos;

//Environment


uniform vec3 EmissiveColor;

struct Enviroment
{
    vec3 I_Fog;
    float zNear, zFar;
    float c1, c2, c3;
};

struct Light
{
//Light
    vec3 Pos;
    float PADDING1;

//material
    float Ka;
    float Kd;
    float Ks;
    float ns;

//Light
    vec3 Ia;
    float PADDING3;
    vec3 Id;
    float PADDING4;
    vec3 Is;
    float PADDING5;
};


layout(std140, binding = 1) uniform LightBlock
{
    Light lights[MAX_NUM_TOTAL_LIGHTS];
    int NumActiveLights;
} light_block;

layout(std140, binding = 2) uniform EnvironmentBlock
{
    Enviroment data;
} environment_block;

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
    for(int i = 0; i < light_block.NumActiveLights; ++i)
    {
        //Light
        vec3 Pos = light_block.lights[i].Pos;

        //material
        float Ka = light_block.lights[i].Ka;
        float Kd = light_block.lights[i].Kd;
        float Ks = light_block.lights[i].Ks;
        vec3 I_Emissive = EmissiveColor * 256;
        float ns = light_block.lights[i].ns;

        //Light
        vec3 Ia = light_block.lights[i].Ia;
        vec3 Id = light_block.lights[i].Id;
        vec3 Is = light_block.lights[i].Is;

        vec3 L = Pos - shading_data.Position;
        //    vec3 L = vec3(1.f, 0.f, 0.f);
        float LightDistance = length(L);
        vec3 L_Normalized = L / LightDistance;

        vec3 N = normalize(shading_data.Normal);

        float NdotL = dot(N, L_Normalized);
        vec3 ReflectionVector = 2 * NdotL * N - L_Normalized;
        float RdotV = dot(ReflectionVector, V_Normalized);
        float Att = min(1.f/(environment_block.data.c1 + environment_block.data.c2 * LightDistance + environment_block.data.c3 * LightDistance * LightDistance), 1.f);


        vec3 I_Ambient = Ia * Ka;
        float diffuse_comp = max(NdotL, 0.f);
        vec3 I_Diffuse = Id * Kd * diffuse_comp;
        vec3 I_Specular = Is * Ks * pow(diffuse_comp > 0.f ? max(RdotV, 0.f) : 0.f, ns);

        //    Att = 1.f;
        Sum_Local_Light += I_Emissive + Att * (I_Ambient + I_Diffuse + I_Specular);
    }
    float S = (environment_block.data.zFar - CameraDistance)/(environment_block.data.zFar - environment_block.data.zNear);
    vec3 I_Local = Sum_Local_Light / light_block.NumActiveLights;
    vec3 I_Fianl = S * I_Local + (1.f - S) * environment_block.data.I_Fog;
    color = I_Fianl / vec3(256.f);
}
