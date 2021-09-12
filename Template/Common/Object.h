//
// Created by yoonki on 9/12/21.
//

#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

#include "Shader.h"

class Object{
public:


private:
    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Shader> mShader;
//    std::shared_ptr<Texture> mTexture;
};
#endif //ENGINE_OBJECT_H
