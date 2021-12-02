/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: CubeObject.h
Purpose: Header file for CubeObject
Language: C++, g++
Platform: gcc version 9.3.0/ Linux / Opengl 4.5 supported GPU required
Project: y.kim_CS300_3
Author: Yoonki Kim, y.kim,  180002421
Creation date: Dec 2, 2021
End Header --------------------------------------------------------*/
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
