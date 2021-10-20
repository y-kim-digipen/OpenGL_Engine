//
// Created by yoonki on 9/12/21.
//

#ifndef ENGINE_TESTSCENE_H
#define ENGINE_TESTSCENE_H

#include <glm/gtx/transform.hpp>
#include <random>
#include "SceneBase.h"
class TestScene : public SceneBase{
public:
    virtual void Init() override
    {
        SceneBase::Init();
        constexpr float orbitRadius = 2.f;
        constexpr float orbitalMoveSphereRadius = 0.2f;
        static auto OrbitsMoveUpdate = [&, initialSetting = true, currentRadian = 0.f, max = 8](int i, Object* obj) mutable {
            //axis y is fixed
            if(initialSetting){
                obj->SetScale(glm::vec3(orbitalMoveSphereRadius));
                currentRadian = PI * 2.f / max * i;
                initialSetting = false;
            }
            if(i > max){
                std::cerr << "Orbit sphere hit max capacity!!" << std::endl;
                return;
            }
            auto pCentralObject = GetObjectList().find("CentralObject")->second;
            glm::vec3 center = pCentralObject->GetPosition();
            glm::vec2 fixedYCenter = glm::vec2(center.x, center.z);
            fixedYCenter += orbitRadius * glm::vec2(std::cos(currentRadian), std::sin(currentRadian));
            obj->SetPosition(glm::vec3(fixedYCenter.x, center.y, fixedYCenter.y));
            obj->SetRotation(glm::vec3(cos(-currentRadian),0.f,sin(-currentRadian)));
            currentRadian += 0.0003f;
        };

        static auto DrawOrbit = [&, initialSetting = true](Object* obj) mutable {
            static std::vector<glm::vec3> orbitLines;
            constexpr int segments = 100;
            static GLuint vertexVBO;

            if(initialSetting){
                orbitLines.reserve(segments * 2);
                glm::vec3 center = obj->GetPosition();
                const float radianMove = PI * 2.f / segments;
                for(float radian = 0.f; radian <= PI * 2.f /*- radianMove*/; radian += radianMove){
                    orbitLines.emplace_back(glm::vec3(std::cos(radian), 0.f , std::sin(radian)) * 0.5f);
                    orbitLines.emplace_back(glm::vec3( std::cos(radian + radianMove), 0.f, std::sin(radian + radianMove)) * 0.5f);
                }

                glGenBuffers(1, &vertexVBO);
                glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
                glBufferData(GL_ARRAY_BUFFER, orbitLines.size() * sizeof(decltype(orbitLines)::value_type), orbitLines.data(), GL_STATIC_DRAW);

                initialSetting = false;
            }

            //////////////Drawing Logic//////////////
            const GLint shaderPID = Engine::GetShader("FaceNormalDrawShader")->GetProgramID();

            //setting&binding buffer
            auto& attributeInfos = Engine::GetShader("FaceNormalDrawShader")->GetAttribInfos();
            const GLuint VAOID = Engine::GetVAOManager().GetVAO( Engine::GetShader("FaceNormalDrawShader")->GetAttributeID());

            glBindVertexArray(VAOID);
            for(auto& attribute : attributeInfos){
                if(attribute.name == "FaceNormalPosition"){
                    glEnableVertexAttribArray(attribute.location);


                    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
                    glVertexAttribPointer( attribute.location,
                                           attribute.DataSize,
                                           attribute.DataType,
                                           GL_FALSE,
                                           0,
                                           (void *) 0 );
                }
            }
            //Drawing Logic
            glUseProgram(shaderPID);
            GLint vTransformLoc = glGetUniformLocation(shaderPID, "vertexTransform");
            if(vTransformLoc < 0){
                std::cerr << "Unable to find uniform variable!" << std::endl;
            }
            const auto& pCam = Engine::GetCurrentScene()->GetCurrentCamera();

            //Get matricies
            glm::mat4 modelToWorldMatrix = obj->GetObjectToWorldMatrix();


            glm::mat4 tempToWorld(1.f);
            tempToWorld = glm::translate(tempToWorld, obj->GetPosition());

            tempToWorld = glm::rotate(tempToWorld, obj->GetRotation().x, glm::vec3{ 1.f, 0.f, 0.f });
            tempToWorld = glm::rotate(tempToWorld, obj->GetRotation().y, glm::vec3{ 0.f, 1.f, 0.f });
            tempToWorld = glm::rotate(tempToWorld, obj->GetRotation().z, glm::vec3{ 0.f, 0.f, 1.f });
            tempToWorld = glm::scale(tempToWorld, obj->GetScale() * orbitRadius * 2.f);

            glm::mat4 viewMatrix = pCam->GetLookAtMatrix();
            glm::mat4 projectionMatrix = pCam->GetPerspectiveMatrix();
            glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * tempToWorld;

            glUniformMatrix4fv(vTransformLoc, 1, GL_FALSE, &mvpMatrix[0][0]);


            //Draw
            glDrawArrays(GL_LINES, 0, orbitLines.size());
            //Clean
            for(auto& attribute : attributeInfos){
                glDisableVertexAttribArray(attribute.location);
            }
            glBindVertexArray(0);
            glUseProgram(0);
        };

        using std::placeholders::_1;
        AddCamera();
        //for initializing camera
        SceneBase::Init();

        auto pCentralObj = AddObject("CentralObject", "Bunny", "3D_DefaultShader");
        pCentralObj->BindFunction(DrawOrbit);

        for(int i = 0; i < 8; ++i){
            std::random_device randomDevice;
            std::uniform_int_distribution<int> randomDistribution(0, 255);
            const std::string& objName = "OrbitObject" + std::to_string(i);
            auto pObj = AddObject(objName, "Sphere", "DiffuseShader");
            pObj->BindFunction(std::bind(OrbitsMoveUpdate,  i, _1));
           Engine::GetShader(pObj->GetUsingShaderName())->GetUniformValue<glm::vec3>(pObj->GetName(), "diffuseColor")
                   = glm::vec3(randomDistribution(randomDevice) / 255.f, randomDistribution(randomDevice) / 255.f, randomDistribution(randomDevice) / 255.f);
        }
    };

    //void InitFromFile(const std::filesystem::path& filePath);

//    virtual void PreRender() override;
//    virtual void Render() override;
//    virtual void PostRender() override;
//
//    virtual void CleanUp() override;

};

#endif //ENGINE_TESTSCENE_H
