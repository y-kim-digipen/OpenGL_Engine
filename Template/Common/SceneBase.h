//
// Created by yoonki on 9/11/21.
//

#ifndef ENGINE_SCENEBASE_H
#define ENGINE_SCENEBASE_H

#include <filesystem>

#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include "LightManager.h"

class SceneBase{
public:
    virtual void Init();

    //todo implement this if needed
    //void InitFromFile(const std::filesystem::path& filePath);

    virtual void PreRender();
    virtual void Render() const;
    virtual void PostRender();

    virtual void CleanUp();

    template<typename... Args>
    void AddCamera(Args... arg);
    void AddCamera();
    void AddCamera(std::shared_ptr<Camera> cam);

    [[nodiscard]] std::shared_ptr<Camera> GetCurrentCamera();
    [[nodiscard]] const std::map<std::string, std::shared_ptr<Object>>& GetObjectList() const;
    [[nodiscard]] const std::map<std::string, std::shared_ptr<Light>>& GetLightList() const;

    std::shared_ptr<Object> AddObject(const std::string& objectName, const std::string& usingMesh, const std::string& usingShader);
protected:
    short mFocusedCameraIdx;

    std::vector<std::shared_ptr<Camera>> m_pCameras;

private:
    std::map<std::string, std::shared_ptr<Object>> m_pObjects;
    std::map<std::string, std::shared_ptr<Light>> m_pLights;
};

#endif //ENGINE_SCENEBASE_H
