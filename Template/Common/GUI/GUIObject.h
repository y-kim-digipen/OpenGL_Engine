//
// Created by yoonki on 9/15/21.
//

#ifndef ENGINE_GUIOBJECT_H
#define ENGINE_GUIOBJECT_H

#include "imgui.h"
namespace GUI {
    class GUI_Object {
    public:
        virtual void Init() {}

        void Update() {
            PreRender();
            Render();
            PostRender();
        }

        virtual void CleanUp() {}

    protected:
        virtual void PreRender() {}

        virtual void Render() = 0;

        virtual void PostRender() {}

        bool mIsOpen;
    };
}
#endif //ENGINE_GUIOBJECT_H
