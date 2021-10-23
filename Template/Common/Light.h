//
// Created by yoonki on 9/14/21.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "Object.h"

class Light : public Object{
    friend class LightManager;
public:
    Light(const std::string& name) : Object(name, "Bulb", "TestShader") {
        SetPosition(glm::vec3(1.f, 1.f, 0.f));
    }
private:
    float Ka = 0.1f;
    float Kd = 0.5f;
    float Ks = 0.8f;
    glm::vec3 I_Emissive = glm::vec3(50, 10, 10);
    float ns = 3.f;

    glm::vec3 Ia = glm::vec3(100, 100, 100), Id = glm::vec3(120, 250, 10), Is = glm::vec3(200, 200, 200);
//    void Render() override;
};

#endif //ENGINE_LIGHT_H
