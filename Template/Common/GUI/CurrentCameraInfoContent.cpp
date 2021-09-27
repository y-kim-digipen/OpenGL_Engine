//
// Created by yoonki on 9/15/21.
//
#include "CurrentCameraInfoContent.h"

#include "Engine.h"
#include "SceneBase.h"
#include "Camera.h"

namespace GUI{

    void CurrentCameraInfoContent::Render() {
        auto camera = GetCurrentActiveCamera().get();
        if(camera != nullptr) {
            static float limit = 10000.f;
            static float movementSpeed = 1.f;
            ImGui::BeginChild(ImGui::GetID("Pos"), ImVec2());
            auto camPos = camera->GetEyePosition();
            auto oldCamPos = camPos;
            ImGui::DragFloat3("CamPos", &camPos.x, movementSpeed, -limit, limit);
            ImGui::SameLine();
            ImGui::InputFloat("Speed", &movementSpeed);
            if(oldCamPos != camPos){
                camera->SetEyePosition(camPos);
            }

            ImGui::EndChildFrame();
        }
    }

    std::shared_ptr<Camera> CurrentCameraInfoContent::GetCurrentActiveCamera() const {
        auto pCurrentScene = Engine::GetCurrentScene();
        if(!pCurrentScene){
            return nullptr;
        }
        return pCurrentScene->GetCurrentCamera();
    }
}
