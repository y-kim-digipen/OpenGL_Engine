//
// Created by yoonki on 9/12/21.
//
#include "SceneBase.h"

void SceneBase::Init() {
    if(m_pCameras.empty() == false){
        mFocusedCameraIdx = 0;
    }
//    auto pLight = m_pLights.emplace("DefaultLight", new Light("DefaultLight")).first->second;
//    pLight->SetScale(glm::vec3(0.2f));
//    pLight->SetPosition(glm::vec3(1.f, 1.f, 0.f));
//
//    pLight = m_pLights.emplace("DefaultLight2", new Light("DefaultLight2")).first->second;
//    pLight->SetScale(glm::vec3(0.2f));
//    pLight->SetPosition(glm::vec3(-3.f, 0.f, 0.f));
////    pLight->std140_structure.I_Emissive = glm::vec3(0.f, 0.f, 230.f);
//    pLight->std140_structure.position = glm::vec3(0.f, 0.f, 3.f);
////    pLight->std140_structure.I_Emissive = glm::vec3(0.f, 59.f, 9.f);
}

void SceneBase::PreRender() {
    for(auto& cam : m_pCameras){
        cam->Update();
    }
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
    for(auto& obj : m_pObjects){
        auto& pObject = obj.second;
        if(pObject->IsRenderReady()){
            pObject->Render();
        }
    }
    for(auto& light : m_pLights){
        auto& pLight = light.second;
        if(pLight->IsRenderReady()) {
            pLight->Render();
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



