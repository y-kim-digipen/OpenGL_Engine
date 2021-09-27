//
// Created by yoonki on 9/15/21.
//

#ifndef ENGINE_ENGINEINFO_H
#define ENGINE_ENGINEINFO_H
#include "GUIWindow.h"

#include <string>
namespace GUI{
    class EngineInfo : public GUI_Window{
    public:
        EngineInfo(const std::string &titleName) : GUI_Window(titleName) {}

        void PreRender() final;
        void Render() final;
        void PostRender() final;
    };
}



#endif //ENGINE_ENGINEINFO_H
