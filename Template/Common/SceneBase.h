/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: BaseScene.h
Purpose: Header file of BaseScene
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#ifndef ENGINE_SCENEBASE_H
#define ENGINE_SCENEBASE_H

#include <filesystem>

#include "Camera.h"
#include "Object.h"

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

    std::shared_ptr<Object> AddObject(const std::string& objectName, const std::string& usingMesh, const std::string& usingShader);
protected:
    short mFocusedCameraIdx;

    std::vector<std::shared_ptr<Camera>> m_pCameras;

private:
    std::map<std::string, std::shared_ptr<Object>> m_pObjects;
};

#endif //ENGINE_SCENEBASE_H
