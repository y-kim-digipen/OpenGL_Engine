/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: CommonConstants.h
Purpose: Declaration of commonly used constants
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#ifndef ENGINE_COMMONCONSTANTS_H
#define ENGINE_COMMONCONSTANTS_H
#include <string>
#include <vector>

#include <GL/glew.h>

constexpr float PI = 3.1415926535f;
constexpr float HALF_PI = PI/2;

enum class DataType
{
    Bool = GL_BOOL, Int = GL_INT, Float = GL_FLOAT, Vec2f = GL_FLOAT_VEC2, Vec3f, Vec4f, Mat3f = GL_FLOAT_MAT3, Mat4f, Count,
};

struct AttributeInfo{
    GLint location;
    std::string name;
    GLenum DataType;
    GLint DataSize;

    bool operator < (const AttributeInfo& rhs) const{
        auto hash = std::hash<std::string>{};
        return (location < rhs.location) && (hash(name) < hash(rhs.name)) && (DataType < rhs.DataType) && (DataSize < rhs.DataSize);
    }
};

using AttributeInfoContainer = std::vector<AttributeInfo>;

#endif //ENGINE_COMMONCONSTANTS_H
