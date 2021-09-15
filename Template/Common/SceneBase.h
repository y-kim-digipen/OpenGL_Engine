//
// Created by yoonki on 9/11/21.
//

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
    void AddCamera(void);
    void AddCamera(std::shared_ptr<Camera> cam);

    [[nodiscard]] std::shared_ptr<Camera> GetCurrentCamera();
protected:
    short mFocusedCameraIdx;

    std::vector<std::shared_ptr<Camera>> m_pCameras;
    std::map<std::string, std::unique_ptr<Object>> m_pObjects;
};

#endif //ENGINE_SCENEBASE_H
