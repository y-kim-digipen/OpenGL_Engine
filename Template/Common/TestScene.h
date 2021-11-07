//
// Created by yoonki on 9/12/21.
//

#ifndef ENGINE_TESTSCENE_H
#define ENGINE_TESTSCENE_H


#include "SceneBase.h"


class TestScene : public SceneBase{
public:
    virtual void Init() override;


    //void InitFromFile(const std::filesystem::path& filePath);

//    virtual void PreRender() override;
//    virtual void Render() override;
//    virtual void PostRender() override;
//
//    virtual void CleanUp() override;

};

#endif //ENGINE_TESTSCENE_H
