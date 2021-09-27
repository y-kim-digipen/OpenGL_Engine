//
// Created by yoonki on 9/12/21.
//
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
    if(mFocusedCameraIdx < 0 || mFocusedCameraIdx >= m_pCameras.size()){
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


