#version 450 core

#define MAX_NUM_TOTAL_LIGHTS 16
uniform vec3 CameraPos_GUIX;

uniform bool UsingTexture_GUIX;

//Environment
uniform vec3 EmissiveColor;

layout (binding = 10) uniform sampler2D tex_object0;
layout (binding = 11) uniform sampler2D tex_object1;

struct Enviroment
{
    vec3 I_Fog;
    float zNear;
    vec3 GlobalAmbient;
    float zFar;
};

struct Light
{
//Light
    vec3 Pos;
    int type;

//material
    float Ka;
    float Kd;
    float Ks;
    float ns;

//Light
    vec3 Ia;
    float c1;
    vec3 Id;
    float c2;
    vec3 Is;
    float c3;

    vec3 dir;
    float theta;
    vec3 padding;
    float phi;

    vec3 DummyPadding;
    float P;
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
    vec2 UV;
} shading_data;



out vec3 color;

//layout(location = 0) out vec3 color;
//layout(location = 1) out float depth;
//layout(location = 2) out vec3 normal;


void main() {
    vec3 Sum_Local_Light = vec3(0.f);

    vec3 V = CameraPos_GUIX - shading_data.Position;
    float CameraDistance = length(V);
    vec3 V_Normalized = V / CameraDistance;
    if(light_block.NumActiveLights > 0)
    {
        for(int i = 0; i < light_block.NumActiveLights; ++i)
        {
            Light currentlight = light_block.lights[i];

            vec3 Pos = currentlight.Pos;

            float CameraDistance = length(V);
            vec3 V_Normalized = V / CameraDistance;

            //material
            float Ka = currentlight.Ka;
            float Kd = currentlight.Kd;
            float Ks = currentlight.Ks;
            float ns = currentlight.ns;

            //Light
            vec3 Ia = currentlight.Ia;
            vec3 Id = currentlight.Id;
            vec3 Is = currentlight.Is;
            if(UsingTexture_GUIX)
            {
                Id = mix(texture(tex_object0, shading_data.UV).rgb * 256.f, currentlight.Id, 0.4f);
                Is = mix(texture(tex_object1, shading_data.UV).rgb * 256.f, currentlight.Is, 0.4f);
                ns = max(texture(tex_object1, shading_data.UV).r, 0.01f);
            }

            vec3 L = Pos - shading_data.Position;
            float LightDistance = length(L);
            vec3 L_Normalized = L / LightDistance;

            vec3 N = normalize(shading_data.Normal);

            float NdotL = dot(N, L_Normalized);
            vec3 ReflectionVector = 2 * NdotL * N - L_Normalized;
            float RdotV = dot(ReflectionVector, V_Normalized);
            float Att = min(1.f/(currentlight.c1 + currentlight.c2 * LightDistance + currentlight.c3 * LightDistance * LightDistance), 1.f);

            vec3 I_Ambient = Ia * Ka;
            vec3 I_Diffuse = Id * Kd * max(NdotL, 0.f);
            vec3 I_Specular = Is * Ks * pow( max(RdotV, 0.f), ns);

            vec3 Local_Light = vec3(0.f);

            switch(currentlight.type)
            {
                case 0: /*PointLight*/
                {
                    Local_Light =  Att * (I_Ambient + I_Diffuse + I_Specular);
                    break;
                }
                case 1: /*DirectionalLight*/
                {
                    break;
                }
                case 2: /*SpotLight*/
                {
                    float P = 1.f;
                    float LdotD = dot(L_Normalized, normalize(currentlight.dir));
                    float SpotLightEffect = 0.f;
                    float cosPhi = cos(currentlight.phi);
                    float cosTheta = cos(currentlight.theta);
                    if(LdotD < cosPhi)
                    {
                        SpotLightEffect = 0.f;
                    }
                    else if(LdotD > cosTheta)
                    {
                        SpotLightEffect = 1.f;
                    }
                    else
                    {
                        SpotLightEffect = pow((LdotD - cos(currentlight.phi)) / (cos(currentlight.theta) - cos(currentlight.phi)), currentlight.P);
                    }
                    Local_Light =  Att * (I_Ambient + SpotLightEffect * (I_Diffuse + I_Specular));
                    break;
                }
            }
            Sum_Local_Light += Local_Light;
        }
    }

    float S = (environment_block.data.zFar - CameraDistance)/(environment_block.data.zFar - environment_block.data.zNear);

    vec3 I_Emissive = EmissiveColor * 256;
    vec3 I_Local = I_Emissive + Sum_Local_Light / light_block.NumActiveLights;
    vec3 I_Fianl = environment_block.data.GlobalAmbient  +S * I_Local + (1.f - S) * environment_block.data.I_Fog;

    color = I_Fianl / vec3(256.f);
//    depth = 1.f;
//    normal = vec3(1.f);
//    glFragColor = color;
}
