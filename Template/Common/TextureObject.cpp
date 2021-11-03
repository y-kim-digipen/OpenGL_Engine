//
// Created by yoonki on 10/31/21.
//

#include "TextureObject.h"

void TextureObject::SetTextureValues(GLuint textureHandle, GLuint width, GLuint height, GLenum textureType,
                                     GLint textureUnit) {
     mTextureHandle = textureHandle;
     mWidth = width, mHeight = height;
     mTextureType = textureType;
     mTextureUnit = textureUnit;
}

void TextureObject::SetTextureShaderName(const std::string &tName) {
    mShaderName = tName;
}

GLint TextureObject::GetTextureUnit() {
    return mTextureUnit;
}

void TextureObject::SetTextureUniform(std::shared_ptr<Shader> pShader) {
    GLint texSamplerLoc = glGetUniformLocation(pShader->GetProgramID(), mShaderName.c_str());
    if(texSamplerLoc >= 0)//Has uniform
    {
        glUniform1i(texSamplerLoc, mTextureUnit);
    }
}

GLenum TextureObject::GetTextureType() {
    return mTextureType;
}

GLuint TextureObject::GetHandle() {
    return mTextureHandle;
}
