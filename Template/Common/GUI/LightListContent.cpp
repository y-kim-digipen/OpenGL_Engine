//
// Created by yoonki on 10/23/21.
//

#include "LightListContent.h"
#include "Engine.h"
#include "GUIWindow.h"
#include "ColorSet.h"
#include "LightDetailContent.h"

namespace GUI{

    void LightListContent::Render() {
        constexpr size_t inputBufferSize = 20;

        auto pCurrentScene = Engine::GetCurrentScene();
        if(pCurrentScene == nullptr){
            return;
        }
        auto& LightList = pCurrentScene->GetLightList();

        for(auto& obj_itr : LightList){

            auto& objNameStr = obj_itr.first;
            ImGui::PushID(objNameStr.c_str());

            std::string inputBuffer(inputBufferSize, ' ');
            memcpy(inputBuffer.data(), objNameStr.c_str(), inputBufferSize + 1);
            ImGui::SetNextItemWidth(150);
            ImGui::AlignTextToFramePadding();
            ImGui::InputText(("##" +  objNameStr).c_str(), inputBuffer.data(), inputBufferSize, ImGuiInputTextFlags_AutoSelectAll);
            if(inputBuffer != objNameStr){
                //todo make name changeable
//            objNameStr = inputBuffer;
            }
            //todo fix bug
            ImGui::SameLine();
            ImGui::SetNextItemWidth(120);
            auto& GUIManager = Engine::GetGUIManager();
            if(!GUIManager.HasWindow(objNameStr)){
                if(ImGui::Button("  Detail  ")){
                    auto pWindow = GUIManager.AddWindow(objNameStr);
                    pWindow->AddFlag(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
                    pWindow->AddContent((objNameStr + " detail").c_str(), new LightDetailContent(obj_itr.second));
                    pWindow->SetCanClose(false);
                }
            }
            else{
                ImGui::PushStyleColor(ImGuiCol_Button, GUI_Color::CollapseButton_Default);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, GUI_Color::CollapseButton_Default);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GUI_Color::CollapseButton_Hover);

                if(ImGui::Button("Collapse")){
                    GUIManager.RemoveWindow(objNameStr);
                }
                ImGui::PopStyleColor(3);
            }

            ImGui::PopID();
        }
    }

}