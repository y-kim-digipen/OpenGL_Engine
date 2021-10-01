/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: BaseScene.cpp
Purpose: Source file of BaseScene
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#include "SceneBase.h"

void SceneBase::Init() {
    if(m_pCameras.empty() == false){
        mFocusedCameraIdx = 0;
    }
}

void SceneBase::PreRender() {
    for(auto& cam : m_pCameras){
        cam->Update();
    }
    for(auto& obj : m_pObjects){
        auto& pObject = obj.second;
        pObject->PreRender();
    }
}

void SceneBase::Render() const {
    for(auto& obj : m_pObjects){
        auto& pObject = obj.second;
        if(pObject->IsRenderReady()){
            pObject->Render();
        }
    }
}

void SceneBase::PostRender() {
    for(auto& obj : m_pObjects){
        auto& pObject = obj.second;
        pObject->PostRender();
    }
}

void SceneBase::CleanUp() {
    m_pObjects.clear();
    m_pCameras.clear();
}

std::shared_ptr<Camera> SceneBase::GetCurrentCamera() {
    if(mFocusedCameraIdx < 0 || mFocusedCameraIdx >= static_cast<short>(m_pCameras.size())){
        return nullptr;
    }
    return m_pCameras[mFocusedCameraIdx];
}

template<typename... Args>
void SceneBase::AddCamera(Args... arg) {
    AddCamera(std::make_shared<Camera>(arg...));
}

void SceneBase::AddCamera(void) {
    AddCamera(std::make_shared<Camera>());
}

void SceneBase::AddCamera(std::shared_ptr<Camera> cam) {
    m_pCameras.emplace_back(cam);
}

const std::map<std::string, std::shared_ptr<Object>> &SceneBase::GetObjectList() const {
    return m_pObjects;
}

std::shared_ptr<Object> SceneBase::AddObject(const std::string &objectName, const std::string &usingMesh, const std::string &usingShader) {
    return  m_pObjects.emplace(objectName, std::make_unique<Object>(objectName, usingMesh, usingShader)).first->second;
}


