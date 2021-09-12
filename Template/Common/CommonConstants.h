//
// Created by yoonki on 9/12/21.
//

#ifndef ENGINE_COMMONCONSTANTS_H
#define ENGINE_COMMONCONSTANTS_H
#include <GL/glew.h>

constexpr float PI = 3.1415926535f;
constexpr float HALF_PI = PI/2;

enum class DataType
{
    Bool = GL_BOOL, Int = GL_INT, Float = GL_FLOAT, Vec2f = GL_FLOAT_VEC2, Vec3f, Vec4f, Mat3f = GL_FLOAT_MAT3, Mat4f, Count,
};

#endif //ENGINE_COMMONCONSTANTS_H
