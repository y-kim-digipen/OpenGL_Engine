//
// Created by yoonki on 11/20/21.
//

#include "FBO.h"
#include "TextureObject.h"
#include "Engine.h"

#include <iostream>
void FBO::Init(GLuint width, GLuint height) {
    mFBOWidth = width;
    mFBOHeight = height;
    glGenFramebuffers(1, &mFBOHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBOHandle);
}

void FBO::SetAttachment(GLenum slot, TextureObject *texture, GLuint level) {
    if(texture->GetSize().first != mFBOWidth || texture->GetSize().second != mFBOHeight)
    {
        std::cerr << "Texture and Framebuffer Dimension mismatch, failed to add attachment to FBO" << std::endl;
        return;
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, slot, texture->GetTextureType(), texture->GetHandle(), level);

    if(mAttachments.find(slot) != mAttachments.end()) //if already in
    {
        mAttachments.erase(mAttachments.find(slot));
        mDrawBuffers.erase(std::find(mDrawBuffers.begin(), mDrawBuffers.end(), slot));
    }
    mAttachments[slot] = texture;
    mDrawBuffers.push_back(slot);

    Engine::GetTextureManager().RegisterFromPointer(std::to_string(mFBOHandle) + "_" + std::to_string(slot) + "_" + std::to_string(texture->GetHandle()), texture);
}

void FBO::SetDepthAttachment() {
    glGenRenderbuffers(1, &mDepthHandle);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mFBOWidth, mFBOHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthHandle);

}

void FBO::UseDrawBuffers() {
    glDrawBuffers(mDrawBuffers.size(), mDrawBuffers.data());
}

std::pair<GLuint, GLuint> FBO::GetFBOSize() {
    return std::pair<GLuint, GLuint>(mFBOWidth, mFBOHeight);
}

GLuint FBO::GetFBOHandle() {
    return mFBOHandle;
}

std::string FBO::GetAttachmentTextureName(GLenum slot) {
    return std::to_string(mFBOHandle) + "_" + std::to_string(slot) + "_" + std::to_string(mAttachments[slot]->GetHandle());
}

TextureObject *FBO::GetTextureAttachment(GLenum slot) {
    return mAttachments[slot];
}
