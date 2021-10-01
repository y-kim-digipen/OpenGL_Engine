/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: VAOManager.h
Purpose: Header file of VAOManager
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#ifndef ENGINE_VAOMANAGER_H
#define ENGINE_VAOMANAGER_H
#include <map>
#include <memory>
#include <vector>

#include <GL/gl.h>
#include "CommonConstants.h"


class Shader;

class VAOManager {
    friend class Shader;
public:
    ~VAOManager();
    void CleanUp();
public:
    GLuint GetVAO(GLuint pAttributeID);
private:
    GLuint GetAttribID(AttributeInfoContainer pAttributes);
    std::map<GLuint, GLuint> mVAOs;
    std::map<AttributeInfoContainer, GLuint> mAttribIDs;
};


#endif //ENGINE_VAOMANAGER_H
