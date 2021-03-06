/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: TestScene.cpp
Purpose: Source file for TestScene
Language: C++, g++
Platform: gcc version 9.3.0/ Linux / Opengl 4.5 supported GPU required
Project: y.kim_CS300_2
Author: Yoonki Kim, y.kim,  180002421
Creation date: Nov 7, 2021
End Header --------------------------------------------------------*/
#include "TestScene.h"
#include <glm/gtx/transform.hpp>
#include <random>
#include "Engine.h"
using std::placeholders::_1;
void TestScene::Init() {
    SceneBase::Init();
    constexpr float orbitRadius = 0.3f;
    [[maybe_unused]]static auto DrawOrbit = [&, initialSetting = true](Object *obj) mutable {
        static std::vector<glm::vec3> orbitLines;
        constexpr int segments = 100;
        static GLuint vertexVBO;

        if (initialSetting) {
            const float radianMove = PI * 2.f / segments;
            for (float radian = 0.f; radian <= PI * 2.f /*- radianMove*/; radian += radianMove) {
                orbitLines.emplace_back(glm::vec3(std::cos(radian), 0.5f, std::sin(radian)) * 0.5f);
                orbitLines.emplace_back(
                        glm::vec3(std::cos(radian + radianMove), 0.5f, std::sin(radian + radianMove)) * 0.5f);
            }

            glGenBuffers(1, &vertexVBO);
            glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
            glBufferData(GL_ARRAY_BUFFER, orbitLines.size() * sizeof(decltype(orbitLines)::value_type),
                         orbitLines.data(), GL_STATIC_DRAW);

            initialSetting = false;
        }

        //////////////Drawing Logic//////////////
        const GLint shaderPID = Engine::GetShader("FaceNormalDrawShader")->GetProgramID();

        //setting&binding buffer
        auto &attributeInfos = Engine::GetShader("FaceNormalDrawShader")->GetAttribInfos();
        const GLuint VAOID = Engine::GetVAOManager().GetVAO(
                Engine::GetShader("FaceNormalDrawShader")->GetAttributeID());

        glBindVertexArray(VAOID);
        for (auto &attribute: attributeInfos) {
            if (attribute.name == "FaceNormalPosition") {
                glEnableVertexAttribArray(attribute.location);


                glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
                glVertexAttribPointer(attribute.location,
                                      attribute.DataSize,
                                      attribute.DataType,
                                      GL_FALSE,
                                      0,
                                      (void *) 0);
            }
        }
        //Drawing Logic
        glUseProgram(shaderPID);
        GLint vTransformLoc = glGetUniformLocation(shaderPID, "vertexTransform");
        if (vTransformLoc < 0) {
            std::cerr << "Unable to find uniform variable!" << std::endl;
        }
        const auto &pCam = Engine::GetCurrentScene()->GetCurrentCamera();

        glm::mat4 tempToWorld(1.f);
        tempToWorld = glm::translate(tempToWorld, obj->GetPosition());

        tempToWorld = glm::rotate(tempToWorld, obj->GetRotation().x, glm::vec3{1.f, 0.f, 0.f});
        tempToWorld = glm::rotate(tempToWorld, obj->GetRotation().y, glm::vec3{0.f, 1.f, 0.f});
        tempToWorld = glm::rotate(tempToWorld, obj->GetRotation().z, glm::vec3{0.f, 0.f, 1.f});
        tempToWorld = glm::scale(tempToWorld, obj->GetScale() * orbitRadius * 2.f);

        glm::mat4 viewMatrix = pCam->GetLookAtMatrix();
        glm::mat4 projectionMatrix = pCam->GetPerspectiveMatrix();
        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * tempToWorld;

        glUniformMatrix4fv(vTransformLoc, 1, GL_FALSE, &mvpMatrix[0][0]);


        //Draw
        glDrawArrays(GL_LINES, 0, orbitLines.size());
        //Clean
        for (auto &attribute: attributeInfos) {
            glDisableVertexAttribArray(attribute.location);
        }
        glBindVertexArray(0);
        glUseProgram(0);
    };


    SceneBase::SetCamera();
    //for initializing camera
    SceneBase::Init();

    auto pCentralObj1 = AddObject("CentralObject", "4Sphere", "FrenselPhong");
    pCentralObj1->SetTextureOption(true);
    pCentralObj1->SetDoEnvironmentMapping(true);

//    auto pCentralObj2 = AddObject("CentralObject2", "Lucy", "RefractionShader");
//    pCentralObj2->SetTextureOption(true);
//    pCentralObj2->SetDoEnvironmentMapping(true);
//    pCentralObj2->SetPosition(glm::vec3(-1.5, 0.f, 0.f));
//
//    auto pCentralObj3 = AddObject("CentralObject3", "Bunny", "ReflectionShader");
//    pCentralObj3->SetTextureOption(true);
//    pCentralObj3->SetDoEnvironmentMapping(true);
//    pCentralObj3->SetPosition(glm::vec3(1.5, 0.f, 0.f));

//    auto pPlaneObj = AddObject("Plane1", "Plane", "PhongShader");
//    pPlaneObj->SetRotation(glm::vec3(-HALF_PI, 0.f, 0.f));
//    pPlaneObj->SetScale(glm::vec3(10.f, 10.f, 1.f));
//    pPlaneObj->SetPosition(glm::vec3(0.f, -0.6f, 0.f));
//    pPlaneObj->SetTextureOption(false);
}


