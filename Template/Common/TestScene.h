//
// Created by yoonki on 9/12/21.
//

#ifndef ENGINE_TESTSCENE_H
#define ENGINE_TESTSCENE_H
#include "SceneBase.h"
class TestScene : public SceneBase{
public:
    virtual void Init() override
    {
        //for initializing camera
        SceneBase::Init();
        m_pObjects.emplace("TestObject", std::make_unique<Object>("TestMesh", "TestShader"));
        m_pObjects.begin()->second->Init();
    };

    //void InitFromFile(const std::filesystem::path& filePath);

//    virtual void PreRender() override;
//    virtual void Render() override;
//    virtual void PostRender() override;
//
//    virtual void CleanUp() override;

};

#endif //ENGINE_TESTSCENE_H
