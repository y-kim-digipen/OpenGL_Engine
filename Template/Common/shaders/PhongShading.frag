#version 420 core

uniform int NumActiveLights = 1;

//material
float Ka = 0.7f;
float Kd = 0.5f;
float Ks = 1.0f;
vec3 I_Emissive = vec3(50, 10, 10) / vec3(256);
uniform float ns = 3.f;

//Light
vec3 Ia = vec3(100, 100, 100) / vec3(256);
vec3 Id = vec3(120, 250, 10) / vec3(256);
vec3 Is = vec3(200, 200, 200) / vec3(256);

uniform vec3 I_Fog = vec3(0.3f);

in PhongShadingData
{
    float NdotL;
    float RdotV;
    float S;
    float Att;
} shading_data;

out vec3 color;

void main() {
    vec3 I_Ambient = Ia * Ka;
    float diffuse_comp = max(shading_data.NdotL, 0.f);
    vec3 I_Diffuse = Id * Kd * diffuse_comp;
    vec3 I_Specular = Is * Ks * pow(diffuse_comp > 0.f ? max(shading_data.RdotV, 0.f) : 0.f, ns);

    vec3 I_Local = I_Emissive + shading_data.Att * (I_Ambient + I_Diffuse + I_Specular);
    vec3 I_Fianl = shading_data.S * I_Local + (1.f - shading_data.S) * I_Fog;
    color = I_Fianl;
}
