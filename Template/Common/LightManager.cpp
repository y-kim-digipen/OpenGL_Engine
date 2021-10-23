//
// Created by yoonki on 10/19/21.
//

#include <cstring>
#include "LightManager.h"
#include "Engine.h"

const int LightManager::GetNumLights() {
    return static_cast<int>(m_pLights.size());
}

void LightManager::CreateBuffer(const std::string shaderName, std::vector<GLint> &offsets) {
    GLuint uboHandle;
    size_t uboSize = offsets.back();
    offsets.pop_back();
    const size_t bufferSize = uboSize * numLights;
    std::vector<char> buffer(bufferSize);
    glGenBuffers(1, &uboHandle);

    std::map<std::string, GLint> offsetData;
    for(int i = 0; i < offsets.size(); ++i){
        std::string nameStr{names[i]};
        offsetData[nameStr] = offsets[i];
    }
    UBOData ubo_data;
    ubo_data.UBOHandle = uboHandle;
    ubo_data.structSize = uboSize;
    ubo_data.offsets = std::move(offsetData);
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
    buffers[shaderName] = std::make_pair(ubo_data, std::move(buffer));

    m_pLights.push_back(std::shared_ptr<Light>(new Light("")));
}

void LightManager::Update() {
    for(auto& buffer : buffers){
//        glUseProgram(Engine::GetShader(buffer.first)->GetProgramID());
        UBOData& curUBOData = buffer.second.first;
        std::vector<char>& data = buffer.second.second;
        glBindBuffer(GL_UNIFORM_BUFFER, curUBOData.UBOHandle);
        int structStartOffset = 0;
        //set values
        for(const auto& light : m_pLights)
        {
            int offset = curUBOData.offsets["LightArray.Pos"];
            glm::vec3 lightPos = light->GetPosition();
            memcpy(data.data() + (structStartOffset + offset), &lightPos, sizeof(lightPos));

            offset = curUBOData.offsets["LightArray.Ka"];
            float Ka = light->Ka;
            memcpy(data.data() + (structStartOffset + offset), &Ka, sizeof(Ka));

            offset = curUBOData.offsets["LightArray.Kd"];
            float Kd = light->Kd;
            memcpy(data.data() + (structStartOffset + offset), &Kd, sizeof(Kd));

            offset = curUBOData.offsets["LightArray.Ks"];
            float Ks = light->Ks;
            memcpy(data.data() + (structStartOffset + offset), &Ks, sizeof(Ks));

            offset = curUBOData.offsets["LightArray.I_Emissive"];
            glm::vec3 I_Emissive = light->I_Emissive;
            memcpy(data.data() + (structStartOffset + offset), &I_Emissive, sizeof(I_Emissive));

            offset = curUBOData.offsets["LightArray.ns"];
            float ns = light->ns;
            memcpy(data.data() + (structStartOffset + offset), &ns, sizeof(ns));

            offset = curUBOData.offsets["LightArray.Ia"];
            glm::vec3 Ia = light->Ia;
            memcpy(data.data() + (structStartOffset + offset), &Ia, sizeof(Ia));

            offset = curUBOData.offsets["LightArray.Id"];
            glm::vec3 Id = light->Id;
            memcpy(data.data() + (structStartOffset + offset), &Id, sizeof(Id));

            offset = curUBOData.offsets["LightArray.Ia"];
            glm::vec3 Is = light->Is;
            memcpy(data.data() + (structStartOffset + offset), &Is, sizeof(Is));

            structStartOffset += curUBOData.structSize;
        }

        glBufferData(GL_UNIFORM_BUFFER, curUBOData.structSize,
                     buffer.second.second.data(), GL_DYNAMIC_DRAW);
//        glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex,
//                         uboHandle);
//        glUseProgram(0);
    }


}
