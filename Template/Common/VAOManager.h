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
    GLuint GetVAO(AttributeInfoContainer pAttributes);
private:
    std::map<AttributeInfoContainer, GLuint> mVAOs;
};


#endif //ENGINE_VAOMANAGER_H
