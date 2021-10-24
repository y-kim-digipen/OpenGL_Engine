//
// Created by yoonki on 10/23/21.
//

#include "LightDetailContent.h"

#include "Engine.h"

namespace GUI
{

    LightDetailContent::LightDetailContent(std::shared_ptr<Light> target) : GUI_Content() {
        m_pTargetLight = target;
    }

    void LightDetailContent::Render() {
        constexpr auto ToFloatColour = [](int r, int g, int b){
            return ImVec4(r/255.f, g/255.f, b/255.f, 1.f);
        };

        if(IsDead()){
            return;
        }
        if(ImGui::BeginTabBar("##TabBar")) {
            if (ImGui::BeginTabItem("LightData")) {
                auto& lightInfo = m_pTargetLight->std140_structure;

                ImGui::DragFloat("Ka", (float*)&lightInfo.Ka, 0.02, 0.f, 1.f);
                ImGui::DragFloat("Kd", (float*)&lightInfo.Kd, 0.02, 0.f, 1.f);
                ImGui::DragFloat("Ks", (float*)&lightInfo.Ks, 0.02, 0.f, 1.f);

//                glm::vec3 I_EmissiveColor = lightInfo.I_Emissive / 256.f;
//                ImGui::ColorEdit3("I_Emissive", (float*)&I_EmissiveColor.x);
//                lightInfo.I_Emissive = I_EmissiveColor * 256.f;

                glm::vec3 I_AColor = lightInfo.Ia / 256.f;
                ImGui::ColorEdit3("Ia", (float*)&I_AColor.x);
                lightInfo.Ia = I_AColor * 256.f;

                glm::vec3 I_DColor = lightInfo.Id / 256.f;
                ImGui::ColorEdit3("Id", (float*)&I_DColor.x);
                lightInfo.Id = I_DColor * 256.f;

                glm::vec3 I_SColor = lightInfo.Is / 256.f;
                ImGui::ColorEdit3("Is", (float*)&I_SColor.x);
                lightInfo.Is = I_SColor * 256.f;
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Assets")) {
                //selectable shader
                const auto &shaderList = Engine::GetShaderManager().GetNameList();
                const std::string &currentShaderName = m_pTargetLight->GetUsingShaderName();
                if (ImGui::BeginCombo("ShaderList", currentShaderName.c_str())) {
                    for (const auto &shaderName: shaderList) {
                        bool isSelected = (currentShaderName == shaderName);
                        if (ImGui::Selectable(shaderName.c_str(), isSelected)) {
                            m_pTargetLight->SetShader(shaderName);
                        }
                        if (isSelected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }

                //selectable mesh
                const auto &meshList = Engine::GetMeshManager().GetNameList();
                const std::string &currentMeshName = m_pTargetLight->GetUsingMeshName();
                if (ImGui::BeginCombo("MeshList", currentMeshName.c_str())) {
                    for (const auto &meshName: meshList) {
                        bool isSelected = (currentMeshName == meshName);
                        if (ImGui::Selectable(meshName.c_str(), isSelected)) {
                            m_pTargetLight->SetMesh(meshName);
                        }
                        if (isSelected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Transforms")) {
                static float sliderSpeed = 0.1f;
                ImGui::InputFloat("SliderSpeed", (float *) &sliderSpeed);
                ImGui::DragFloat3("Position", (float *) &m_pTargetLight->m_position, sliderSpeed);
                ImGui::DragFloat3("Scale", (float *) &m_pTargetLight->m_scale, sliderSpeed);
                ImGui::DragFloat3("Rotation", (float *) &m_pTargetLight->m_rotation, sliderSpeed);
                ImGui::EndTabItem();
            }

            /////////
            if (ImGui::BeginTabItem("ShaderUniforms")) {
                const std::string& objName = m_pTargetLight->mObjectName;
                auto pShader = m_pTargetLight->m_pShader;
                auto &uniforms = pShader->GetUniforms();
                for (auto &uniformAttrib: uniforms) {
                    std::string name = uniformAttrib.first;
                    switch (uniformAttrib.second.mType) {
                        case DataType::Bool: {
                            GLboolean *value = &pShader->GetUniformValue<GLboolean>(objName, name);
                            ImGui::NextColumn();
                            ImGui::Text("%s", name.c_str());
                            ImGui::NextColumn();
                            ImGui::Checkbox(("##" + name).c_str(), reinterpret_cast<bool *>(value));
                            break;
                        }
                        case DataType::Int: {
                            GLint *value = &pShader->GetUniformValue<GLint>(objName, name);
                            ImGui::NextColumn();
                            ImGui::Text("%s", name.c_str());
                            ImGui::NextColumn();
                            ImGui::DragInt(("##" + name).c_str(), value);
                            break;
                        }
                        case DataType::Float: {
                            GLfloat *value = &pShader->GetUniformValue<GLfloat>(objName, name);
                            ImGui::NextColumn();
                            ImGui::Text("%s", name.c_str());
                            ImGui::NextColumn();
                            ImGui::DragFloat(("##" + name).c_str(), value, 0.1f);
                            break;
                        }
                        case DataType::Vec2f: {
                            glm::vec2 *value = &pShader->GetUniformValue<glm::vec2>(objName, name);
                            ImGui::NextColumn();
                            ImGui::Text("%s", name.c_str());
                            ImGui::NextColumn();
                            ImGui::DragFloat2(("##" + name).c_str(), &value->x, 0.1f);
                            break;
                        }
                        case DataType::Vec3f: {
                            glm::vec3 *value = &pShader->GetUniformValue<glm::vec3>(objName, name);
                            ImGui::NextColumn();
                            ImGui::Text("%s", name.c_str());
                            ImGui::NextColumn();
                            if (name.find("color") < name.size() | name.find("Color") < name.size()) {
                                ImGui::ColorEdit3(("##" + name).c_str(), &value->x);
                            } else {

                                ImGui::DragFloat3(("##" + name).c_str(), &value->x, 0.1f);
                            }
                            break;
                        }
                        case DataType::Vec4f: {
                            glm::vec4 *value = &pShader->GetUniformValue<glm::vec4>(objName, name);
                            ImGui::NextColumn();
                            ImGui::Text("%s", name.c_str());
                            ImGui::NextColumn();
                            if (name.find("color") < name.size() | name.find("Color") < name.size()) {
                                ImGui::ColorEdit4(("##" + name).c_str(), &value->x);
                            } else {
                                ImGui::DragFloat4(("##" + name).c_str(), &value->x, 0.1f);
                            }
                            break;
                        }
                        case DataType::Mat3f: {
                            //glm::mat3* value = &pShader->GetUniformValue<glm::mat3>(name);
                            //ImGui::DragFloat3(name.c_str(), value->operator[](0));
                            break;
                        }
                        case DataType::Mat4f: {
//                SetUniformMatrix4f(name.c_str(), GetUniformValue<glm::mat4>(name));
                            break;
                        }
                        default: {
                            /*throw "Logic error";*/
                            break;
                        }
                    }
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }

    void LightDetailContent::CleanUp() {
        m_pTargetLight.reset();
    }

    bool LightDetailContent::IsDead() {
        return m_pTargetLight == nullptr;
    }

    bool LightDetailContent::DoDestroyBaseWindow() {
        return IsDead();
    }
}