//
// Created by yoonki on 9/14/21.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "Object.h"
namespace GUI{
    class LightDetailContent;
}
class Light : public Object{
    friend class GUI::LightDetailContent;
    friend class LightManager;
public:
    Light(const std::string& lightName) : Object(lightName, "Bulb", "TestShader") {
        SetPosition(glm::vec3(1.f, 1.f, 0.f));
    }

    Light(const std::string& lightName, const std::string& meshName, const std::string& shaderName) : Object(lightName, meshName, shaderName) { }

    void PreRender() override
    {
        std140_structure.position = GetPosition();
        Object::PreRender();
    }

    void* GetSTD140Structure(){
        return &std140_structure.position;
    }

    static GLint GetSTD140StructureSize()
    {
        return sizeof(std140);
    }

public:
    struct std140{
        glm::vec3 position; /*just update base classes position, it is just for padding*/
        float dummy1;
        float Ka = 0.1f;
        float Kd = 0.5f;
        float Ks = 0.8f;
        float ns = 3.f;

        glm::vec3 Ia = glm::vec3(250, 50, 50);
        float dummy3;
        glm::vec3 Id = glm::vec3(120, 250, 10);
        float dummy4;
        glm::vec3 Is = glm::vec3(2, 200, 2);
        float dummy5;
    } std140_structure;
//    void Render() override;

};

#endif //ENGINE_LIGHT_H
