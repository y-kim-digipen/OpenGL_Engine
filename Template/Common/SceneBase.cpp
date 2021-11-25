/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: SceneBase.cpp
Purpose: Source file for SceneBase
Language: C++, g++
Platform: gcc version 9.3.0/ Linux / Opengl 4.5 supported GPU required
Project: y.kim_CS300_2
Author: Yoonki Kim, y.kim,  180002421
Creation date: Nov 7, 2021
End Header --------------------------------------------------------*/
#include <iostream>
#include "SceneBase.h"
#include "Engine.h"

#include "CubeObject.h"
#include "Object.h"

void SceneBase::Init() {
    FSQ_Obj = new Object("Quad", "Quad", "FSQ Shader");
    FSQ_Obj->Init();
    FSQ_Obj->ChangeTexture(0, Engine::FSQ_FBO.GetAttachmentTextureName(GL_COLOR_ATTACHMENT0));
    FSQ_Obj->ChangeTexture(1, "");


    FSQ_Obj2 = new Object("Quad2", "Quad", "FSQ Shader");
    FSQ_Obj2->Init();
//    FSQ_Obj2->ChangeTexture(0, Engine::EnvironmentMappingFBO.GetAttachmentTextureName(GL_COLOR_ATTACHMENT0));
    FSQ_Obj2->ChangeTexture(0, "rightDiffuseBuffer");
    FSQ_Obj2->ChangeTexture(1, "");

    FSQ_Obj3 = new Object("Quad3", "Quad", "FSQ Shader");
    FSQ_Obj3->Init();
//    FSQ_Obj2->ChangeTexture(0, Engine::EnvironmentMappingFBO.GetAttachmentTextureName(GL_COLOR_ATTACHMENT0));
    FSQ_Obj3->ChangeTexture(0, "leftDiffuseBuffer");
    FSQ_Obj3->ChangeTexture(1, "");

    FSQ_Obj4 = new Object("Quad4", "Quad", "FSQ Shader");
    FSQ_Obj4->Init();
//    FSQ_Obj2->ChangeTexture(0, Engine::EnvironmentMappingFBO.GetAttachmentTextureName(GL_COLOR_ATTACHMENT0));
    FSQ_Obj4->ChangeTexture(0, "topDiffuseBuffer");
    FSQ_Obj4->ChangeTexture(1, "");

    FSQ_Obj5 = new Object("Quad5", "Quad", "FSQ Shader");
    FSQ_Obj5->Init();
//    FSQ_Obj2->ChangeTexture(0, Engine::EnvironmentMappingFBO.GetAttachmentTextureName(GL_COLOR_ATTACHMENT0));
    FSQ_Obj5->ChangeTexture(0, "bottomDiffuseBuffer");
    FSQ_Obj5->ChangeTexture(1, "");

    FSQ_Obj6 = new Object("Quad6", "Quad", "FSQ Shader");
    FSQ_Obj6->Init();
//    FSQ_Obj2->ChangeTexture(0, Engine::EnvironmentMappingFBO.GetAttachmentTextureName(GL_COLOR_ATTACHMENT0));
    FSQ_Obj6->ChangeTexture(0, "frontDiffuseBuffer");
    FSQ_Obj6->ChangeTexture(1, "");

    FSQ_Obj7 = new Object("Quad7", "Quad", "FSQ Shader");
    FSQ_Obj7->Init();
//    FSQ_Obj2->ChangeTexture(0, Engine::EnvironmentMappingFBO.GetAttachmentTextureName(GL_COLOR_ATTACHMENT0));
    FSQ_Obj7->ChangeTexture(0, "backDiffuseBuffer");
    FSQ_Obj7->ChangeTexture(1, "");

    CubeMap_Obj = new CubeObject();
    CubeMap_Obj->Init();
}


void SceneBase::PreRender() {
    m_pCamera->Update();
    for(auto& obj : m_pObjects){
        auto& pObject = obj.second;
        pObject->PreRender();
    }
    for(auto& light : m_pLights){
        auto& pLight = light.second;
        pLight->PreRender();
    }
}

void SceneBase::Render() const {
    UseFBO(Engine::FSQ_FBO.GetFBOHandle(), Engine::GetWindowSize().x, Engine::GetWindowSize().y);
    RenderCubeMap();
    for(auto& obj : m_pObjects){

        auto& pObject = obj.second;
        if(pObject->IsRenderReady()){
            pObject->Render();
        }
    }
    for(auto& light : m_pLights) {
        auto &pLight = light.second;
        if (pLight->IsRenderReady()) {
            pLight->Render();
        }
    }
//    RenderCubeMap();
    glDisable(GL_DEPTH_TEST);
    UseFBO(0, Engine::GetWindowSize().x, Engine::GetWindowSize().y, true);
    FSQ_Obj->Render();

//    glViewport(0, 0, Engine::GetWindowSize().x * 0.1667, Engine::GetWindowSize().x * 0.1667);
//    glLoadIdentity();
//    FSQ_Obj2->Render();
//
//    glViewport(Engine::GetWindowSize().x * 0.1667, 0, Engine::GetWindowSize().x * 0.1667, Engine::GetWindowSize().x * 0.1667);
//    glLoadIdentity();
//    FSQ_Obj3->Render();
//
//    glViewport(Engine::GetWindowSize().x * 0.1667 * 2, 0, Engine::GetWindowSize().x * 0.1667, Engine::GetWindowSize().x * 0.1667);
//    glLoadIdentity();
//    FSQ_Obj4->Render();
//
//    glViewport(Engine::GetWindowSize().x * 0.1667 * 3, 0, Engine::GetWindowSize().x * 0.1667, Engine::GetWindowSize().x * 0.1667);
//    glLoadIdentity();
//    FSQ_Obj5->Render();
//
//    glViewport(Engine::GetWindowSize().x * 0.1667 * 4, 0, Engine::GetWindowSize().x * 0.1667, Engine::GetWindowSize().x * 0.1667);
//    glLoadIdentity();
//    FSQ_Obj6->Render();
//
//    glViewport(Engine::GetWindowSize().x * 0.1667 * 5, 0, Engine::GetWindowSize().x * 0.1667, Engine::GetWindowSize().x * 0.1667);
//    glLoadIdentity();
//    FSQ_Obj7->Render();

    glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderForEnvironmentMapping() {
    RenderCubeMap();
    //For environment mapping
    for(auto& obj : m_pObjects){
        auto& pObject = obj.second;
        if(pObject->IsRenderReady()){
            if(pObject->DoEnvironmentMapping() == false)
            {
                pObject->Render();
            }
        }
    }
    for(auto& light : m_pLights){
        auto& pLight = light.second;
        if(pLight->IsRenderReady()) {
            if(pLight->DoEnvironmentMapping() == false)
            {
                pLight->Render();
            }
        }
    }
}

void SceneBase::PostRender() {
    for(auto& obj : m_pObjects){
        auto& pObject = obj.second;
        pObject->PostRender();
    }
    for(auto& light : m_pLights){
        auto& pLight = light.second;
        if(pLight->IsRenderReady()) {
            pLight->PostRender();
        }
    }

}

void SceneBase::CleanUp() {
    m_pObjects.clear();
}

std::shared_ptr<Camera> SceneBase::GetCurrentCamera() {
   return m_pCamera;
}

template<typename... Args>
void SceneBase::SetCamera(Args... arg) {
    return SetCamera(std::make_shared<Camera>(arg...));
}

void SceneBase::SetCamera(std::shared_ptr<Camera> cam) {
    m_pCamera = cam;
}

const std::map<std::string, std::shared_ptr<Object>> &SceneBase::GetObjectList() const {
    return m_pObjects;
}

std::shared_ptr<Object> SceneBase::AddObject(const std::string &objectName, const std::string &usingMesh, const std::string &usingShader) {
    return  m_pObjects.emplace(objectName, std::make_unique<Object>(objectName, usingMesh, usingShader)).first->second;
}

const std::map<std::string, std::shared_ptr<Light>> &SceneBase::GetLightList() const {
    return m_pLights;
}

std::shared_ptr<Light> SceneBase::AddLight(const std::string &objectName, const std::string &usingMesh, const std::string &usingShader) {
    return  m_pLights.emplace(objectName, std::make_unique<Light>(objectName, usingMesh, usingShader)).first->second;
}

Environment &SceneBase::GetEnvironment() {
    return mEnvironment;
}

unsigned SceneBase::GetNumActiveLights() const {
    return m_pLights.size();
}

void SceneBase::RemoveLight(const std::string &lightName) {
    m_pLights.erase(m_pLights.find(lightName));
}

void SceneBase::ClearLights() {
    m_pLights.clear();
}

std::shared_ptr<Object> SceneBase::GetObject(const std::string &objName) {
    return m_pObjects[objName];
}

void SceneBase::UseFBO(GLuint FBOHandle, GLuint viewportWidth, GLuint viewportHeight, bool clearBuffer, GLuint viewportStartX,GLuint viewportStartY ) const {

    glBindFramebuffer(GL_FRAMEBUFFER, FBOHandle);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Cannot switch to FBO " << FBOHandle << std::endl;
        std::cerr << "[FBO Error] Frame Buffer Incomplete" << std::endl;
        return;
    }
    glViewport(viewportStartX, viewportStartY, viewportWidth, viewportHeight);
    if(clearBuffer)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void SceneBase::RenderCubeMap() const {
    CubeMap_Obj->Render();
}

SceneBase::~SceneBase() {
    delete CubeMap_Obj;
    delete FSQ_Obj;
}

