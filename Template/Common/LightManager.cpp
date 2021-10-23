//
// Created by yoonki on 10/19/21.
//

#include "LightManager.h"

const int LightManager::GetNumLights() {
    return static_cast<int>(m_pLights.size());
}

void LightManager::CreateBuffer(std::vector<GLint> &offsets) {
    GLuint uboHandle;
    size_t uboSize = offsets.back();
    offsets.pop_back();
    std::vector<char> buffer(uboSize * numLights);
    glGenBuffers(1, &uboHandle);

    std::map<std::string, GLint> offsetData;
    for(int i = 0; i < offsets.size(); ++i){
        std::string nameStr{names[i]};
        offsetData[nameStr] = offsets[i];
    }
//    for(const char* name : names){
//        std::string nameStr{name};
//        offsetData[nameStr] =
//    }
//    glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
//    glBufferData(GL_UNIFORM_BUFFER, offsets.back(),
//                 buffer, GL_DYNAMIC_DRAW);
//
//    glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex,
//                     uboHandle);
}

void LightManager::Update() {
    for()
    glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
    glBufferData(GL_UNIFORM_BUFFER, offsets.back(),
                 buffer, GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex,
                     uboHandle);
}
