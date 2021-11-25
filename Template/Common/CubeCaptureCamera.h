//
// Created by yoonki on 11/21/21.
//

#ifndef ENGINE_CUBECAPTURECAMERA_H
#define ENGINE_CUBECAPTURECAMERA_H

#include <vector>
#include <memory>
#include <glm/vec3.hpp>

class Camera;
class Object;
class CubeCaptureCamera{
public:
    CubeCaptureCamera(const std::shared_ptr<Object>& owner);
    ~CubeCaptureCamera();
    void Update();
    std::shared_ptr<Camera> GetCamera(int slot);
private:
    std::shared_ptr<Object> mOwner;
    std::vector<std::shared_ptr<Camera>> mAttachedCameras;
};


#endif //ENGINE_CUBECAPTURECAMERA_H
