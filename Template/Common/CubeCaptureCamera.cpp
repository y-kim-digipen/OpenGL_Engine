//
// Created by yoonki on 11/21/21.
//

#include <iostream>
#include "CubeCaptureCamera.h"
#include "Camera.h"
#include "Object.h"
CubeCaptureCamera::CubeCaptureCamera(const std::shared_ptr<Object>& owner) : mOwner{owner} {
    //    +X = 0
    //    -X
    //    +Y
    //    -Y
    //    +Z
    //    -Z = 5
    mAttachedCameras.reserve(6);
    Camera* pRightCam = new Camera(glm::vec3{0.f}, glm::vec3{1.f, 0.f, 0.f}, glm::vec3{0.f, 1.f, 0.f}, HALF_PI, 1.f, 0.1f, 10.f);
    mAttachedCameras.emplace_back(pRightCam);

    Camera* pLeftCam = new Camera(glm::vec3{0.f}, glm::vec3{-1.f, 0.f, 0.f}, glm::vec3{0.f, 1.f, 0.f}, HALF_PI, 1.f, 0.1f, 10.f);
    mAttachedCameras.emplace_back(pLeftCam);

    Camera* pTopCam = new Camera(glm::vec3{0.f}, glm::vec3{0.f, 1.f, 0.f}, glm::vec3{0.f, 0.f, 1.f}, HALF_PI, 1.f, 0.1f, 10.f);
    mAttachedCameras.emplace_back(pTopCam);

    Camera* pBottomCam = new Camera(glm::vec3{0.f}, glm::vec3{0.f, -1.f, 0.f}, glm::vec3{0.f, 0.f, -1.f}, HALF_PI, 1.f, 0.1f, 10.f);
    mAttachedCameras.emplace_back(pBottomCam);

    Camera* pFrontCam = new Camera(glm::vec3{0.f}, glm::vec3{0.f, 0.f, 1.f}, glm::vec3{0.f, 1.f, 0.f}, HALF_PI, 1.f, 0.1f, 10.f);
    mAttachedCameras.emplace_back(pFrontCam);

    Camera* pBackCam = new Camera(glm::vec3{0.f}, glm::vec3{0.f, 0.f, -1.f}, glm::vec3{0.f, 1.f, 0.f}, HALF_PI, 1.f, 0.1f, 10.f);
    mAttachedCameras.emplace_back(pBackCam);
}

CubeCaptureCamera::~CubeCaptureCamera() {
//    for(Camera* cam : mAttachedCameras)
//    {
//        delete cam;
//    }
    mAttachedCameras.clear();
}

std::shared_ptr<Camera> CubeCaptureCamera::GetCamera(int slot) {
    if(slot < 0 || slot > static_cast<int>(mAttachedCameras.size()))
    {
        std::cerr << "[Cube Mapping Camera] Trying to use invalid camera from " << ((mOwner == nullptr) ? "Invalid Owner " : mOwner->GetName()) << std::endl;
        return nullptr;
    }
    return mAttachedCameras[slot];
}

void CubeCaptureCamera::Translate(const glm::vec3 &amount) {
    const glm::vec3 currentCamPos = mAttachedCameras.front()->GetEyePosition();
    for(auto& cam : mAttachedCameras)
    {
        cam->SetPosition(currentCamPos + amount);
    }
}

void CubeCaptureCamera::Rotate(const glm::vec3 &amount) {
    for(auto& cam : mAttachedCameras)
    {
        cam->Yaw(amount.x);
        cam->Pitch(amount.y);
        cam->Roll(amount.z);
    }
}
