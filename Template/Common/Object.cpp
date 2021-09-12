//
// Created by yoonki on 9/12/21.
//
#include "Object.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine.h"

Object::Object(std::shared_ptr<Mesh> pMesh, std::shared_ptr<Shader> pShader)
    : m_pMesh(pMesh), m_pShader(pShader),
    m_position(), m_scale(1.f), m_rotation(0.f) {}

Object::Object(const std::string &meshStr, const std::string &shaderStr)
    : Object(Engine::GetMesh(meshStr), Engine::GetShader(shaderStr)) {}

void Object::Init() {
    //todo change this after mesh and shader implementation is completed
    if(m_pMesh != nullptr){
        m_pMesh->initData();
    }
    if(m_pShader != nullptr){
        //todo implement this when shader's init is implemented
        //m_pShader->Reload();
    }
}

void Object::Render() const {
    m_pShader->Use();
//    m_pMesh->

    glBindVertexArray(0);
    m_pShader->UnUse();
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

