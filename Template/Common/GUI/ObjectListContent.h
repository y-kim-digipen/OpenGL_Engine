//
// Created by yoonki on 9/16/21.
//

#ifndef ENGINE_OBJECTLISTCONTENT_H
#define ENGINE_OBJECTLISTCONTENT_H

#include <memory>
#include "GUIContent.h"
#include "../Object.h"
namespace GUI{

    class ObjectListContent : public GUI_Content {
    private:
        virtual void Init() {}
        virtual void CleanUp() {}
        void Render() final;
    };
}


#endif //ENGINE_OBJECTLISTCONTENT_H
