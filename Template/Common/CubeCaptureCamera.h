/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: CubeCaptureCamera.h
Purpose: Header file for CubeCaptureCamera
Language: C++, g++
Platform: gcc version 9.3.0/ Linux / Opengl 4.5 supported GPU required
Project: y.kim_CS300_3
Author: Yoonki Kim, y.kim,  180002421
Creation date: Dec 2, 2021
End Header --------------------------------------------------------*/

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
    void Translate(const glm::vec3& amount);
    void Rotate(const glm::vec3& amount);
    std::shared_ptr<Camera> GetCamera(int slot);
private:
    std::shared_ptr<Object> mOwner;
    std::vector<std::shared_ptr<Camera>> mAttachedCameras;
};


#endif //ENGINE_CUBECAPTURECAMERA_H
