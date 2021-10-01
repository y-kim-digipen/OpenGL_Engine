//
// Created by yoonki on 9/17/21.
//

#include <GL/glew.h>
#include "VAOManager.h"
#include "Shader.h"

VAOManager::~VAOManager() {
    CleanUp();
}

GLuint VAOManager::GetVAO(GLuint pAttributeID) {
    if(mVAOs.find(pAttributeID) == mVAOs.end()){

        GLuint VAOID;
        glGenVertexArrays(1, &VAOID);

        mVAOs.emplace(pAttributeID, VAOID);
    }
    return mVAOs[pAttributeID];
}


GLuint VAOManager::GetAttribID(AttributeInfoContainer pAttributes) {
    if(mAttribIDs.find(pAttributes) == mAttribIDs.end()) {
        static GLuint idGenerator = 0;
        mAttribIDs.emplace(pAttributes, idGenerator++);
    }
    return mAttribIDs[pAttributes];
}


void VAOManager::CleanUp() {
    for(const auto& attrib : mVAOs) {
        glDeleteVertexArrays(1, &attrib.second);
    }
}
