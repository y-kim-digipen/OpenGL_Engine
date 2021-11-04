//
// Created by yoonki on 11/3/21.
//

#include "EngineInfoContent.h"
#include "Engine.h"

#include <random>
namespace GUI
{
    void EngineInfoContent::Render() {
        static bool DoRearrangeOrbit = true;
        DoRearrangeOrbit = false;
        static bool firstStart = true;

        using std::placeholders::_1;
        static int numOrbitLights = 8;
//        numOrbitLights = Engine::GetCurrentScene()->GetNumActiveLights();
        constexpr float orbitRadius = 1.5f;
        constexpr float orbitalMoveSphereRadius = 0.2f;

        static float firstOrbitLightRadian = 0.f;

        static auto OrbitsMoveUpdate = [&, currentRadian = 0.f](int i, Object* obj) mutable {
            //axis y is fixed
            if(DoRearrangeOrbit){
                obj->SetScale(glm::vec3(orbitalMoveSphereRadius));
                currentRadian = firstOrbitLightRadian + PI * 2.f / (numOrbitLights + 1) * i;
            }
            auto pCentralObject = Engine::GetCurrentScene()->GetObjectList().find("CentralObject")->second;
            glm::vec3 center = pCentralObject->GetPosition();
            glm::vec2 fixedYCenter = glm::vec2(center.x, center.z);
            fixedYCenter += orbitRadius * glm::vec2(std::cos(currentRadian), std::sin(currentRadian));
            obj->SetPosition(glm::vec3(fixedYCenter.x, center.y + 1.f, fixedYCenter.y));
            obj->SetRotation(glm::vec3(cos(-currentRadian),0.f,sin(-currentRadian)));
            static_cast<Light*>(obj)->std140_structure.dir = obj->GetPosition() + glm::vec3(0.f, 0.5f, 0.f) - pCentralObject->GetPosition();
            currentRadian += 0.003f;
            firstOrbitLightRadian += 0.003f / numOrbitLights;
        };

        if(firstStart)
        {
            for(int i = 0; i < numOrbitLights; ++i){
                std::random_device randomDevice;
                std::uniform_int_distribution<int> randomDistribution(0, 255);
                const std::string& objName = "OrbitObject" + std::to_string(i);
                auto pLight = Engine::GetCurrentScene()->AddLight(objName, "Sphere", "PhongShader");
                pLight->BindFunction(std::bind(OrbitsMoveUpdate,  i, _1));
                glm::vec3 randomColor = glm::vec3(randomDistribution(randomDevice) / 255.f, randomDistribution(randomDevice) / 255.f, randomDistribution(randomDevice) / 255.f);
//           Engine::GetShader(pLight->GetUsingShaderName())->GetUniformValue<glm::vec3>(pLight->GetName(), "diffuseColor")
//                   = randomColor;
                pLight->SetColor(Color(randomColor.x, randomColor.y, randomColor.z));
                pLight->std140_structure.Ia = randomColor * 128.f;
                pLight->std140_structure.Id = randomColor * 180.f;
                pLight->std140_structure.Is = randomColor * 230.f;

                pLight->std140_structure.type = Light::LightType::SPOT_LIGHT;
            }
            firstStart = false;
            DoRearrangeOrbit = true;
        }


        static std::vector<std::string> Scenarios {"Scenario1", "Scenario2", "Scenario3"};
        static std::string currentScenario = Scenarios.front();
        ImGui::ColorEdit3("GlobalAmbient", &Engine::GlobalAmbientColor.x);
        ImGui::ColorEdit3("FogColor", &Engine::FogColor.x);
        if(ImGui::Button("AddLight"))
        {
            const int i = Engine::GetCurrentScene()->GetNumActiveLights();
            if(i < ENGINE_SUPPORT_MAX_LIGHTS)
            {
                numOrbitLights = i;
                std::random_device randomDevice;
                std::uniform_int_distribution<int> randomDistribution(0, 255);
                const std::string& objName = "OrbitObject" + std::to_string(i);
                auto pLight = Engine::GetCurrentScene()->AddLight(objName, "Sphere", "PhongShader");
                pLight->BindFunction(std::bind(OrbitsMoveUpdate,  i, _1));
                glm::vec3 randomColor = glm::vec3(randomDistribution(randomDevice) / 255.f, randomDistribution(randomDevice) / 255.f, randomDistribution(randomDevice) / 255.f);
                pLight->SetColor(Color(randomColor.x, randomColor.y, randomColor.z));
                pLight->std140_structure.Ia = randomColor * 128.f;
                pLight->std140_structure.Id = randomColor * 180.f;
                pLight->std140_structure.Is = randomColor * 230.f;

                pLight->std140_structure.type = Light::LightType::SPOT_LIGHT;
                DoRearrangeOrbit = true;
            }

        }
        ImGui::SameLine();
        if(ImGui::Button("RemoveLight"))
        {
            const int i = Engine::GetCurrentScene()->GetNumActiveLights() - 1;
            if(i != 0)
            {
                Engine::GetCurrentScene()->RemoveLight("OrbitObject" + std::to_string(i));
                numOrbitLights = i;
                DoRearrangeOrbit = true;
            }
        }

        if(ImGui::BeginCombo("Scenario", currentScenario.c_str())){
            for (const auto &Scenario : Scenarios) {
                bool isSelected = (currentScenario == Scenario);
                if (ImGui::Selectable(Scenario.c_str(), isSelected)) {

                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        static bool update = true;
        if(ImGui::Checkbox("UpdateOrbitMove", &update))
        {
            auto& lights = Engine::GetCurrentScene()->GetLightList();
            for(auto& light : lights)
            {
                if(light.first.find("OrbitObject") <= light.first.length())
                {
                    light.second->SetFunctionUpdate(update);
                }
            }
        }

    }

}
