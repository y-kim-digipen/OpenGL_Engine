//
// Created by yoonki on 9/17/21.
//

#include <GL/glew.h>
#include "VAOManager.h"
#include "Shader.h"

VAOManager::~VAOManager() {
    CleanUp();
}

GLuint VAOManager::GetVAO(AttributeInfoContainer pAttributes) {
    if(mVAOs.find(pAttributes) == mVAOs.end()){
        const GLsizei numAttributes = pAttributes.size();

        GLuint VAOID;
        glGenVertexArrays(1, &VAOID);

        mVAOs.emplace(pAttributes, VAOID);
    }
    return mVAOs[pAttributes];
}

void VAOManager::CleanUp() {
    //todo add
}
