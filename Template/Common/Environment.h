//
// Created by yoonki on 10/23/21.
//

#ifndef ENGINE_ENVIRONMENT_H
#define ENGINE_ENVIRONMENT_H
class Environment
{
public:
    void* GetSTD140Structure(){
        return &std140_structure.I_Fog.x;
    }

    static GLint GetSTD140StructureSize()
    {
        return sizeof(std140);
    }

public:
    struct std140
    {
        glm::vec3 I_Fog;
        float zNear, zFar;
        float c1 = 0.1, c2 = 0.005, c3 = 0.0025;
    } std140_structure;
};
#endif //ENGINE_ENVIRONMENT_H
