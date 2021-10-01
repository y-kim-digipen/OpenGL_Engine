/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: VBOManager.cpp
Purpose: Source file of VBOManager
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#include <GL/glew.h>
#include "VBOManager.h"
#include "Mesh.h"

void VBOManager::SetUpVBO(Mesh* pMesh) {
    const std::string& meshName = pMesh->mName;
    auto& VBOInfoCont = mVBOInfos[meshName].first;
    if(!VBOInfoCont.empty()){
        //todo delete buffers
        VBOInfoCont.clear();
    }

    //Position
    {
        GLuint posVBO;
        glGenBuffers(1, &posVBO);
        glBindBuffer(GL_ARRAY_BUFFER, posVBO);
        glBufferData(GL_ARRAY_BUFFER, pMesh->vertexBuffer.size() * sizeof(decltype(pMesh->vertexBuffer)::value_type), pMesh->vertexBuffer.data(), GL_STATIC_DRAW);
        VBOInfoCont.emplace("vPosition", posVBO);
    }
    //Normal
    {
        GLuint normalVBO;
        glGenBuffers(1, &normalVBO);
        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glBufferData(GL_ARRAY_BUFFER, pMesh->vertexNormals.size() * sizeof(decltype(pMesh->vertexNormals)::value_type), pMesh->vertexNormals.data(), GL_STATIC_DRAW);
        VBOInfoCont.emplace("vertexNormal", normalVBO);
    }
    //UV
    {
        GLuint uvVBO;
        glGenBuffers(1, &uvVBO);
        glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
        glBufferData(GL_ARRAY_BUFFER, pMesh->vertexUVs.size() * sizeof(decltype(pMesh->vertexUVs)::value_type), pMesh->vertexUVs.data(), GL_STATIC_DRAW);
        VBOInfoCont.emplace("vUV", uvVBO);
    }
    //VertexNormalDisplay
    {
        GLuint vertexVBO;
        glGenBuffers(1, &vertexVBO);
        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, pMesh->vertexNormalDisplay.size() * sizeof(decltype(pMesh->vertexNormalDisplay)::value_type), pMesh->vertexNormalDisplay.data(), GL_STATIC_DRAW);
        VBOInfoCont.emplace("vertexNormalPosition", vertexVBO);
    }

    //FaceNormalDisplay
    {
        GLuint vertexVBO;
        glGenBuffers(1, &vertexVBO);
        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, pMesh->vertexFaceNormalsDisplay.size() * sizeof(decltype(pMesh->vertexFaceNormalsDisplay)::value_type), pMesh->vertexFaceNormalsDisplay.data(), GL_STATIC_DRAW);
        VBOInfoCont.emplace("FaceNormalPosition", vertexVBO);
    }

    //Index
    {
        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, pMesh->vertexIndices.size() * sizeof(decltype(pMesh->vertexIndices)::value_type), pMesh->vertexIndices.data(), GL_STATIC_DRAW);
        mVBOInfos[meshName].second = EBO;
    }
}

std::pair<std::map<std::string, GLuint>, GLuint> &VBOManager::GetVBOInfo(std::shared_ptr<Mesh> pMesh) {
    return mVBOInfos[pMesh->GetName()];
}

void VBOManager::CleanUp() {
    for(const auto& vboInfo : mVBOInfos){
        glDeleteBuffers(1, &vboInfo.second.second);
    }
}
