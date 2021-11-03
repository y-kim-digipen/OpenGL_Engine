//
// Created by yoonki on 10/23/21.
//

#ifndef ENGINE_LIGHTLISTCONTENT_H
#define ENGINE_LIGHTLISTCONTENT_H
#include "GUIContent.h"
namespace GUI
{
    class LightListContent : public GUI_Content {
    private:
        virtual void Init() {}
        virtual void CleanUp() {}
        void Render() final;
    };
}

#endif //ENGINE_LIGHTLISTCONTENT_H
