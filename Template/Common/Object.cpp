//
// Created by yoonki on 9/12/21.
//
#include "Object.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "Engine.h"
Object::Object() : Object(std::shared_ptr<Mesh>(), std::shared_ptr<Shader>()){

}


Object::Object(std::shared_ptr<Mesh> pMesh, std::shared_ptr<Shader> pShader)
    : m_pMesh(pMesh), m_pShader(pShader),
    m_position(), m_scale(1.f), m_rotation(0.f), mToWorldMatrix(1.f), m_MatrixCacheDirty(true) {}

Object::Object(const std::string &meshStr, const std::string &shaderStr)
    : Object(Engine::GetMesh(meshStr), Engine::GetShader(shaderStr)) {}

void Object::Init() {
    //todo change this after mesh and shader implementation is completed
    if(m_pMesh != nullptr){
//        m_pMesh->SetupBuffer();
    }
    if(m_pShader != nullptr){
        //todo implement this when shader's init is implemented
        //m_pShader->Reload();
    }
//    m_rotation = glm::vec3(1.f);
}

void Object::PreRender() {
    //todo just for debugging.
//    m_rotation.z += 0.01f;
//    m_rotation.x += 0.01f;
    m_MatrixCacheDirty = true;
    TryCalculateMatrix();
}

void Object::Render() const {
    const GLint shaderPID = m_pShader->GetProgramID();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(shaderPID);

    GLint vTransformLoc = glGetUniformLocation(shaderPID, "vertexTransform");
    if(vTransformLoc < 0){
        std::cerr << "Unable to find uniform variable!" << std::endl;
    }

    const GLuint meshVAOID = m_pMesh->GetVAOID();
    const GLint shaderAttribCount = Shader::ShaderAttribNames.size();
    std::vector<GLint> usingAttribIndicies;
    usingAttribIndicies.reserve(shaderAttribCount);

    for(GLint AttribIdx = 0; AttribIdx < shaderAttribCount; ++AttribIdx){
        if(m_pShader->GetAttribUsages()[AttribIdx] == true){
            usingAttribIndicies.push_back(AttribIdx);
            glEnableVertexAttribArray(AttribIdx);
            glBindBuffer(GL_ARRAY_BUFFER, m_pMesh->GetEBOID(AttribIdx));
            GLint size;
            GLenum dataType;

            switch(static_cast<Shader::ShaderAttrib>(AttribIdx)){
                //todo change this to using declval/decltype
                case Shader::POS: [[fallthrough]];
                case Shader::NORMAL:{
                    size = 3;
                    dataType = GL_FLOAT;
                    break;
                }
                case Shader::UV:{
                    size = 3;
                    dataType = GL_FLOAT;
                    break;
                }
                case Shader::COLOR:{
                    //todo not supported yet
                    break;
                }
            }
            glVertexAttribPointer(
                    static_cast<GLuint>(AttribIdx),
                    size,
                    dataType,
                    GL_FALSE,
                    0,
                    (void*)0 );
        }
    }

    GLfloat angleOfRotation = 0.f;
    // Draw the triangle !
    // T * R * S * Vertex
    glm::mat4 modelViewPerspectiveMatrix = glm::mat4(1.0f);
//    glm::vec3 scaleVector = glm::vec3(1.0f);
//    glm::vec3 centroid = glm::vec3( -0.5f, -0.5f, 0.0f );
//    modelViewPerspectiveMatrix = glm::rotate(angleOfRotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
//               glm::scale( scaleVector ) *
//               glm::translate( centroid );
    glm::mat4 modelToWorldMatrix = GetObjectToWorldMatrix();
    const auto& pCam = Engine::GetCurrentScene()->GetCurrentCamera();
    glm::mat4 viewMatrix = pCam->GetLookAtMatrix();
//    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 projectionMatrix = pCam->GetPerspectiveMatrix();
    modelViewPerspectiveMatrix = projectionMatrix * viewMatrix * modelToWorldMatrix;
    glUniformMatrix4fv(vTransformLoc, 1, GL_FALSE, &modelViewPerspectiveMatrix[0][0]);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    if(m_pMesh->DoIndexing()){
        glDrawElements(GL_TRIANGLES, m_pMesh->getVertexIndicesCount(), GL_UNSIGNED_INT, (void*) 0);
    }
    else{
        glDrawArrays(GL_TRIANGLES, 0, m_pMesh->getVertexCount());
    }
    for(const GLint& idx : usingAttribIndicies){
        glDisableVertexAttribArray(idx);
    }
    glUseProgram(0);
}

void Object::PostRender() {

}

void Object::CleanUp() const {

}

bool Object::SetShader(const std::string &shaderStr) {
    auto pShader = Engine::GetShader(shaderStr);
    if(pShader){
        m_pShader = pShader;
        //todo init shader here
//        m_pShader->
    }
    return pShader != nullptr;
}

bool Object::SetMesh(const std::string &meshStr) {
    auto pMesh = Engine::GetMesh(meshStr);
    if(pMesh){
        //todo init mesh here
        m_pMesh = pMesh;
    }
    return pMesh != nullptr;
}

bool Object::IsRenderReady() const {
    return m_pShader && m_pMesh;
}

void Object::TryCalculateMatrix() {
    if(m_MatrixCacheDirty){
        glm::mat4 tempToWorld{1.f};


        tempToWorld = glm::scale(tempToWorld, m_scale);
        tempToWorld = glm::rotate(tempToWorld, m_rotation.x, glm::vec3{1.f, 0.f, 0.f});
        tempToWorld = glm::rotate(tempToWorld, m_rotation.y, glm::vec3{ 0.f, 1.f, 0.f });
        tempToWorld = glm::rotate(tempToWorld, m_rotation.z, glm::vec3{ 0.f, 0.f, 1.f });
        tempToWorld = glm::translate(tempToWorld, m_position);

        mToWorldMatrix = tempToWorld;
        m_MatrixCacheDirty = false;
    }
}

glm::mat4 Object::GetObjectToWorldMatrix() const {

    return mToWorldMatrix;
}



