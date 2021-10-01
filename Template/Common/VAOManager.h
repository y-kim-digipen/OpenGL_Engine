//
// Created by yoonki on 9/17/21.
//

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
