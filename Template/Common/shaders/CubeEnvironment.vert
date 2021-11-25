#version 450 core

uniform mat4 vertexTransform;
uniform mat4 vertexNormalTransform;

in layout(location = 0) vec3 vPosition;


out VS_OUT
{
    vec3 vertexPosition;
//    +X = 0
//    -X
//    +y
//    -Y
//    +Z
//    -Z = 5
} vs_out;


void main() {

    //Calculate Cube Map
//    vs_out.vertexPosition = mat3(vertexTransform) * vPosition;
    vs_out.vertexPosition = vPosition;
    gl_Position = vertexTransform * vec4(vPosition, 1.f);
//    gl_Position = vertexTransform * vec4(vPosition, 1.f);
}


//
//out VS_OUT
//{
//    vec2 vertexUV;
//    flat int plane;
////    +X = 0
////    -X
////    +y
////    -Y
////    +Z
////    -Z = 5
//} vs_out;
//
//
//void main() {
//    gl_Position = vertexTransform * vec4(vPosition, 1.f);
//    //Calculate Cube Map
//
//    vec3 vEntity = (vertexTransform * vec4(vPosition, 1.f)).xyz;
//    vec3 absVec = abs(vEntity);
//    vec2 uv = vec2(0.f);
//    int plane;
//    if(absVec.x >= absVec.y && absVec.x >= absVec.z) //abs x is biggest
//    {
//        ( vEntity.x < 0.f ) ? (uv.x = vEntity.z, plane = 0) : (uv.x = -vEntity.z, plane = 1);
//        uv.y = vEntity.y;
//    }
//    else if (absVec.y >= absVec.x && absVec.y >= absVec.z)  //abs y is biggest
//    {
//        (vEntity.y < 0.f) ? (uv.x = vEntity.z, plane = 2) : (uv.x = -vEntity.z, plane = 3);
//        uv.y = vEntity.x;
//    }
//    else //abs z is biggest
//    {
//        (vEntity.z < 0.f) ? (uv.x = -vEntity.x, plane = 4) : (uv.x = vEntity.x, plane = 5);
//        uv.y = vEntity.y;
//    }
//
//    vs_out.vertexUV = (uv + vec2(1.f)) * 0.5f;
//    vs_out.plane = plane;
//}
