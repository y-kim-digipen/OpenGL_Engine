/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: SceneBase.h
Purpose: Header file for SceneBase
Language: C++, g++
Platform: gcc version 9.3.0/ Linux / Opengl 4.5 supported GPU required
Project: y.kim_CS300_2
Author: Yoonki Kim, y.kim,  180002421
Creation date: Nov 7, 2021
End Header --------------------------------------------------------*/

#ifndef ENGINE_SCENEBASE_H
#define ENGINE_SCENEBASE_H

#include <filesystem>

#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include "Environment.h"

class CubeObject;

class SceneBase{
public:
    virtual void Init();
    virtual ~SceneBase();
    //todo implement this if needed
    //void InitFromFile(const std::filesystem::path& filePath);

    virtual void PreRender();
    virtual void Render() const;
    virtual void RenderForEnvironmentMapping();
    virtual void PostRender();

    virtual void CleanUp();

    template<typename... Args>
    void SetCamera(Args... arg);
    void SetCamera(std::shared_ptr<Camera> cam = std::make_shared<Camera>());

    [[nodiscard]] std::shared_ptr<Camera> GetCurrentCamera();
    [[nodiscard]] const std::map<std::string, std::shared_ptr<Object>>& GetObjectList() const;
    [[nodiscard]] const std::map<std::string, std::shared_ptr<Light>>& GetLightList() const;

    std::shared_ptr<Object> AddObject(const std::string& objectName, const std::string& usingMesh, const std::string& usingShader);
    std::shared_ptr<Light> AddLight(const std::string& lightName, const std::string& usingMesh, const std::string& usingShader);
    void RemoveLight(const std::string& lightName);
    void ClearLights();

    unsigned GetNumActiveLights() const;

    std::shared_ptr<Object> GetObject(const std::string& objName);

    Environment& GetEnvironment();

    void UseFBO(GLuint FBOHandle, GLuint viewportWidth, GLuint viewportHeight, bool clearBuffer = true, GLuint viewportStartX = 0,GLuint viewportStartY = 0) const;

    [[maybe_unused]] void RenderCubeMap() const;
protected:
    std::shared_ptr<Camera> m_pCamera;
    Environment mEnvironment;

private:
    Object* FSQ_Obj;
    Object* FSQ_Obj2;
    Object* FSQ_Obj3;
    Object* FSQ_Obj4;
    Object* FSQ_Obj5;
    Object* FSQ_Obj6;
    Object* FSQ_Obj7;
    CubeObject* CubeMap_Obj;
    std::map<std::string, std::shared_ptr<Object>> m_pObjects;
    std::map<std::string, std::shared_ptr<Light>> m_pLights;
};

#endif //ENGINE_SCENEBASE_H
