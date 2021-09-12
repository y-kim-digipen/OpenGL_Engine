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
