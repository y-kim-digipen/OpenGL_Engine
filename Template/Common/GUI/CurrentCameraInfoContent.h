//
// Created by yoonki on 9/15/21.
//

#ifndef ENGINE_CURRENTCAMERAINFOCONTENT_H
#define ENGINE_CURRENTCAMERAINFOCONTENT_H
#include <memory>

#include "GUIContent.h"
#include "Camera.h"
namespace GUI{
    class CurrentCameraInfoContent : public GUI_Content{
    private:
        virtual void Init() {}
        virtual void CleanUp() {}

        void Render() override;

    private:
        [[nodiscard]] std::shared_ptr<Camera> GetCurrentActiveCamera() const;
    };
}
#endif //ENGINE_CURRENTCAMERAINFOCONTENT_H
