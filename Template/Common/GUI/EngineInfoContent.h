//
// Created by yoonki on 11/3/21.
//

#ifndef ENGINE_ENGINEINFOCONTENT_H
#define ENGINE_ENGINEINFOCONTENT_H
#include "GUIContent.h"
namespace GUI
{
    class EngineInfoContent : public GUI_Content {
    public:
        EngineInfoContent() = default;
        void Init() override {}
        void CleanUp() override{}

        void Render() override;

    };
};



#endif //ENGINE_ENGINEINFOCONTENT_H
