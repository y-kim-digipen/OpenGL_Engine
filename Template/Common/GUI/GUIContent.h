//
// Created by yoonki on 9/15/21.
//

#ifndef ENGINE_GUICONTENT_H
#define ENGINE_GUICONTENT_H
#include "GUIObject.h"
namespace GUI {
    class GUI_Content {
    public:
        virtual void Init() = 0;
        virtual void CleanUp() = 0;

        virtual void Render() = 0;

        virtual bool IsDead() { return false; }
        virtual bool DoDestroyBaseWindow() { return false; }
    };
}
#endif //ENGINE_GUICONTENT_H
