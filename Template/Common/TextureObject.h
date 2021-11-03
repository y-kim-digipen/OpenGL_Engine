//
// Created by yoonki on 10/31/21.
//

#ifndef ENGINE_TEXTUREOBJECT_H
#define ENGINE_TEXTUREOBJECT_H

#include "GL/glew.h"
#include "Shader.h"
#include <string>

class TextureObject {
public:
    void SetTextureValues(GLuint textureHandle, GLuint width, GLuint height, GLenum textureType, GLint textureUnit);
    void SetTextureShaderName(const std::string& tName);
    GLint GetTextureUnit();
    GLenum GetTextureType();
    GLuint GetHandle();
    void SetTextureUniform(std::shared_ptr<Shader> pShader);
private:
    GLuint mTextureHandle;
    GLuint mWidth, mHeight;
    GLenum mTextureType;
    GLint mTextureUnit;

    std::string mShaderName;
};


#endif //ENGINE_TEXTUREOBJECT_H
