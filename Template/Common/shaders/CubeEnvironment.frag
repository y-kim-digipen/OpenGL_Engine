#version 450 core

layout (binding = 0) uniform sampler2D Right;
layout (binding = 1) uniform sampler2D Left;
layout (binding = 2) uniform sampler2D Top;
layout (binding = 3) uniform sampler2D Bottom;
layout (binding = 4) uniform sampler2D Front;
layout (binding = 5) uniform sampler2D Back;

in VS_OUT
{
    vec3 vertexPosition;
//    +X = 0
//    -X
//    +y
//    -Y
//    +Z
//    -Z = 5
} fs_in;

out vec3 color;

void main() {
    vec3 vEntity = fs_in.vertexPosition;
    vec3 absVec = abs(vEntity);
    vec2 uv = vec2(0.f);
    int plane;
    if (absVec.x >= absVec.y && absVec.x >= absVec.z)//abs x is biggest
    {
        (vEntity.x < 0.f) ? (uv.x = vEntity.z, plane = 0) : (uv.x = -vEntity.z, plane = 1);
        uv.y = vEntity.y;
    }
    else if (absVec.y >= absVec.x && absVec.y >= absVec.z)//abs y is biggest
    {
        (vEntity.y < 0.f) ? (uv.x = -vEntity.x, plane = 3, uv.y = -vEntity.z) : (uv.x = -vEntity.x, plane = 2, uv.y = vEntity.z);
    }
    else //abs z is biggest
    {
        (vEntity.z < 0.f) ? (uv.x = -vEntity.x, plane = 4) : (uv.x = vEntity.x, plane = 5);
        uv.y = vEntity.y;
    }
    uv.y = -uv.y;
    uv = (uv + vec2(1.f)) * 0.5f;

    vec3 Color = vec3(1.f);
    switch (plane)
    {
        case 0:
        {
            Color = texture(Right, uv).rgb;
            break;
        }
        case 1:
        {
            Color = texture(Left, uv).rgb;
            break;
        }
        case 2:
        {
            Color = texture(Top, uv).rgb;
            break;
        }
        case 3:
        {
            Color = texture(Bottom, uv).rgb;
            break;
        }
        case 4:
        {
            Color = texture(Front, uv).rgb;
            break;
        }
        case 5:
        {
            Color = texture(Back, uv).rgb;
            break;
        }
    }

    color = Color;

    //    color = vec3(1.f);

}


//in VS_OUT
//{
//    vec2 vertexUV;
//    flat int plane;
////    +X = 0
////    -X
////    +y
////    -Y
////    +Z
////    -Z = 5
//} fs_in;
//
//out vec3 color;
//
//void main() {
//    vec3 Color = vec3(1.f);
//    vec2 vertexUV = fs_in.vertexUV;
//
//    switch(fs_in.plane)
//    {
//        case 0:
//        {
//            Color = texture(Right, vertexUV).rgb;
//            break;
//        }
//        case 1:
//        {
//            Color = texture(Left, vertexUV).rgb;
//            break;
//        }
//        case 2:
//        {
//            Color = texture(Top, vertexUV).rgb;
//            break;
//        }
//        case 3:
//        {
//            Color = texture(Bottom, vertexUV).rgb;
//            break;
//        }
//        case 4:
//        {
//            Color = texture(Front, vertexUV).rgb;
//            break;
//        }
//        case 5:
//        {
//            Color = texture(Back, vertexUV).rgb;
//            break;
//        }
//    }
//
//    color = Color;
//
////    color = vec3(1.f);
//}
