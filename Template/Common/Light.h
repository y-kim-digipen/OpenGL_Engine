//
// Created by yoonki on 9/14/21.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "Object.h"

class Light : public Object{
public:
    Light(const std::string& name) : Object(name, "Bulb", "TestShader") {}

//    void Render() override;
};

#endif //ENGINE_LIGHT_H
