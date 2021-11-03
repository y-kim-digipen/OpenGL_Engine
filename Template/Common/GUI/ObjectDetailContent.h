//
// Created by yoonki on 9/17/21.
//

#ifndef ENGINE_OBJECTDETAILCONTENT_H
#define ENGINE_OBJECTDETAILCONTENT_H

#include <memory>

#include "Object.h"
#include "GUIContent.h"
namespace GUI{
    class ObjectDetailContent : public GUI_Content{
    public:
        explicit ObjectDetailContent(std::shared_ptr<Object> target);
        void Init() override {}
        void CleanUp() override;

        void Render() override;

        bool IsDead() override;
        bool DoDestroyBaseWindow() override;
    private:
        std::shared_ptr<Object> m_pTargetObject;
    };




}



#endif //ENGINE_OBJECTDETAILCONTENT_H
