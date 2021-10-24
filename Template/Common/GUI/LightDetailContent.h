//
// Created by yoonki on 10/23/21.
//

#ifndef ENGINE_LIGHTDETAILCONTENT_H
#define ENGINE_LIGHTDETAILCONTENT_H
#include "GUIContent.h"
#include <memory>
#include "../Light.h"
namespace GUI{
    class LightDetailContent : public GUI_Content{
    public:
        explicit LightDetailContent(std::shared_ptr<Light> target);
        void Init() override {}
        void CleanUp() override;

        void Render() override;

        bool IsDead() override;
        bool DoDestroyBaseWindow() override;
    private:
        std::shared_ptr<Light> m_pTargetLight;
    };
}




#endif //ENGINE_LIGHTDETAILCONTENT_H
