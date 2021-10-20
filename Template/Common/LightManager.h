//
// Created by yoonki on 10/19/21.
//

#ifndef ENGINE_LIGHTMANAGER_H
#define ENGINE_LIGHTMANAGER_H
#include <vector>
#include <map>
#include <memory>

#include "Light.h"
class LightManager {
public:
    inline static char *names[] =
            {
                    "LightArray.Pos",
                    "LightArray.Ka",
                    "LightArray.Kd",
                    "LightArray.Ks",
                    "LightArray.I_Emissive",
                    "LightArray.ns",
                    "LightArray.Ia",
                    "LightArray.Id",
                    "LightArray.Is",
            };

    void Update();
    [[nodiscard]] const int GetNumLights();
private:
    struct UBOData
    {
        GLint UBOHandle;
        std::vector<GLint> offsets;
    };
    std::map<std::string/*shader name*/, std::pair<UBOData, std::vector<char>/*buffer*/>> buffers;
    std::vector<std::shared_ptr<Light>> m_pLights;
};


#endif //ENGINE_LIGHTMANAGER_H
