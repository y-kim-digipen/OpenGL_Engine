//
// Created by yoonki on 11/20/21.
//
#include <iostream>
#include <GL/glew.h>
#include "FBO.h"
//#include <GL/gl.h>
//#include <GL/glew.h>
#include "TextureObject.h"
FBO::~FBO() {
    glDeleteFramebuffers(1, &mFBOHandle);
}

void FBO::Init(GLint width, GLint height) {
    m_width = width;
    m_height = height;
    glGenFramebuffers(1, &mFBOHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBOHandle);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        throw("");
    }
}

bool FBO::AddAttachment(GLint slot, TextureObject *pTextureObject, GLuint level) {
    if(pTextureObject->GetTextureSize().first != m_width || pTextureObject->GetTextureSize().second != m_height)
    {
        std::cerr << "FBO and Texture Object "  << pTextureObject->GetHandle() << " Dimension mismatch, failed to add attachment !!" << std::endl;
        return false;
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, slot, pTextureObject->GetTextureType(), pTextureObject->GetHandle(), level);
    mAttachments[slot] = pTextureObject;
    mDrawBuffers.push_back(slot);
    return true;
}

void FBO::AddDepthAttachment() {
    glGenRenderbuffers(1, &mDepthRenderHandle);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthRenderHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_ATTACHMENT, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRenderHandle);
}

void FBO::UseDrawBuffers() {
    glDrawBuffers(mDrawBuffers.size(), mDrawBuffers.data());
}

