//
// Created by yoonki on 9/11/21.
//

#ifndef ENGINE_SCENEBASE_H
#define ENGINE_SCENEBASE_H

#include <filesystem>

#include "Object.h"

class SceneBase{
public:
    virtual void Init() = 0;

    //void InitFromFile(const std::filesystem::path& filePath);

    virtual void PreRender() = 0;
    virtual void Render() = 0;
    virtual void PostRender() = 0;

    virtual void CleanUp() = 0;


protected:
    ComponentManager<Object> mObjects;
};

#endif //ENGINE_SCENEBASE_H
