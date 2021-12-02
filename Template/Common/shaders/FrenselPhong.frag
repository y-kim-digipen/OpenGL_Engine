#version 450 core

#define MAX_NUM_TOTAL_LIGHTS 16
layout (binding = 0) uniform sampler2D rightDiffuseBuffer;
layout (binding = 1) uniform sampler2D leftDiffuseBuffer;
layout (binding = 2) uniform sampler2D topDiffuseBuffer;
layout (binding = 3) uniform sampler2D bottomDiffuseBuffer;
layout (binding = 4) uniform sampler2D frontDiffuseBuffer;
layout (binding = 5) uniform sampler2D backDiffuseBuffer;

layout (binding = 10) uniform sampler2D tex_object0;
layout (binding = 11) uniform sampler2D tex_object1;

uniform vec3 CameraPos_GUIX;

uniform bool UsingTexture_GUIX;
uniform vec3 EmissiveColor;

uniform float FrenselPhongMixRatio = 0.5f;

uniform float EtoR = 0.85;
uniform float EtoG = 0.87;
uniform float EtoB = 0.89;

in VS_OUT
{
    vec3 vertexPosition;
    vec3 vertexNormal;
    vec2 UV;
} fs_in;

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
    vec3 PhongColor = vec3(0.f);
    {
        vec3 Sum_Local_Light = vec3(0.f);

        vec3 V = CameraPos_GUIX - fs_in.vertexPosition;
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
                    Id = mix(texture(tex_object0, fs_in.UV).rgb * 256.f, currentlight.Id, 0.4f);
                    Is = mix(texture(tex_object1, fs_in.UV).rgb * 256.f, currentlight.Is, 0.4f);
                    ns = max(texture(tex_object1, fs_in.UV).r, 0.01f);
                }

                vec3 L = Pos - fs_in.vertexPosition;
                float LightDistance = length(L);
                vec3 L_Normalized = L / LightDistance;

                vec3 N = normalize(fs_in.vertexNormal);

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

        PhongColor = I_Fianl / vec3(256.f);
    }


    vec3 FrenselColor = vec3(0.f);
    {
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
        if(FrenselPhongMixRatio < 0.f)
        {
            FrenselColor = ReflectionColor;
        }
        else if(FrenselPhongMixRatio > 1.f)
        {
            FrenselColor = RefractionColor;
        }
        else
        {
            FrenselColor = mix(RefractionColor, ReflectionColor, Ratio);
        }
    }

//    vec3 FinalColor = RefractionColor;
    if(FrenselPhongMixRatio >= 0.f && FrenselPhongMixRatio <= 1.f)
    {
        Color = mix(FrenselColor, PhongColor, FrenselPhongMixRatio);
    }
    else
    {
        Color = FrenselColor;
    }
}
