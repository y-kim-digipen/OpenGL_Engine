//
// Created by yoonki on 11/21/21.
//

#ifndef ENGINE_CUBEOBJECT_H
#define ENGINE_CUBEOBJECT_H
#include "Object.h"

class CubeObject final : public Object {
public:
    CubeObject();
    ~CubeObject() = default;
private:
    virtual void TryCalculateMatrix() override;
    void RenderModel() const override;
};


#endif //ENGINE_CUBEOBJECT_H
