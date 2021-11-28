//
// Created by yoonki on 11/21/21.
//

#include <glm/gtx/transform.hpp>
#include "CubeObject.h"
#include "Engine.h"
#include "SceneBase.h"

CubeObject::CubeObject() : Object("CubeMapObject", "Cube", "CubeEnvironmentShader") {
    mTextureSlots.clear();
    mTextureSlots.resize(6);

    ChangeTexture(0, "Right");
    ChangeTexture(1, "Left");
    ChangeTexture(2, "Top");
    ChangeTexture(3, "Bottom");
    ChangeTexture(4, "Front");
    ChangeTexture(5, "Back");
}

void CubeObject::RenderModel() const {
    glDisable(GL_CULL_FACE);
//    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    const GLint shaderPID = m_pShader->GetProgramID();

    //setting&binding buffer
    auto& attributeInfos = m_pShader->GetAttribInfos();
    const GLuint VAOID = Engine::GetVAOManager().GetVAO(m_pShader->GetAttributeID());

    auto& VBOInfo = Engine::GetVBOManager().GetVBOInfo(m_pMesh);

    if(mUsingTexture){
        for(const std::string& textureName : mTextureSlots)
        {
            if(textureName.length() == 0)
            {
                continue;
            }
            TextureObject* pTextureObj = Engine::GetTextureManager().FindTextureByName(textureName);
            Engine::GetTextureManager().BindTexture(pTextureObj);
            pTextureObj->SetTextureUniform(m_pShader);
        }
    }

    glBindVertexArray(VAOID);
    for(auto& attribute : attributeInfos){
        glEnableVertexAttribArray(attribute.location);

        glBindBuffer(GL_ARRAY_BUFFER, VBOInfo.first[attribute.name]);
        glVertexAttribPointer( attribute.location,
                               attribute.DataSize,
                               attribute.DataType,
                               GL_FALSE,
                               0,
                               (void *) 0 );
    }
    //setup EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOInfo.second);

    //Drawing Logic
    glUseProgram(shaderPID);
    GLint vTransformLoc = glGetUniformLocation(shaderPID, "vertexTransform");

    const auto& pCam = Engine::GetCurrentScene()->GetCurrentCamera();

    //Get matricies
    [[maybe_unused]]glm::mat4 modelToWorldMatrix = GetObjectToWorldMatrix();
    [[maybe_unused]]glm::mat4 viewMatrix = pCam->GetLookAtMatrix();
    [[maybe_unused]]glm::mat4 projectionMatrix = pCam->GetPerspectiveMatrix();

    [[maybe_unused]]glm::mat4 mvpMatrix = projectionMatrix * pCam->GetCubeMapMatrix();
    [[maybe_unused]]glm::mat4 normalMatrix = projectionMatrix * viewMatrix;

    m_pShader->SetAllUniforms(mObjectName);

    glUniformMatrix4fv(vTransformLoc, 1, GL_FALSE, &mvpMatrix[0][0]);

    glDrawElements(GL_TRIANGLES, m_pMesh->getVertexIndicesCount(), GL_UNSIGNED_INT, (void*) 0);

    for(auto& attribute : attributeInfos){
        glDisableVertexAttribArray(attribute.location);
    }
    glBindVertexArray(0);
    glUseProgram(0);

    glEnable(GL_CULL_FACE);
//    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

void CubeObject::TryCalculateMatrix() {
    if(m_MatrixCacheDirty){
        glm::mat4 tempToWorld{1.f};

        const auto meshBoundingBox = m_pMesh->GetBoundingBox();
        glm::vec3 meshSize = (meshBoundingBox.second - meshBoundingBox.first);
        glm::vec3 meshCenter = (meshBoundingBox.second + meshBoundingBox.first) * 0.5f;


        //set to the bounding box height
        tempToWorld = glm::scale(tempToWorld, 1.f / glm::vec3(meshSize.y));

        tempToWorld = glm::translate(tempToWorld, -meshCenter);

        mToWorldMatrix = tempToWorld;
        m_MatrixCacheDirty = false;
    }
}
