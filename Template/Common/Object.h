//
// Created by yoonki on 9/12/21.
//

#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

#include <memory>

#include "Shader.h"
#include "Mesh.h"


class Object{
public:
    Object() = default;
    Object(std::shared_ptr<Mesh> pMesh, std::shared_ptr<Shader> pShader);
    Object(const std::string& meshStr, const std::string& shaderStr);
    void Init();
    void Render() const;

    void CleanUp() const;
    //todo implement this
    bool SetShader(const std::string& shaderStr);
    bool SetMesh(const std::string& meshStr);

    [[nodiscard]] bool IsRenderReady() const;

private:

private:
    std::shared_ptr<Mesh> m_pMesh;
    std::shared_ptr<Shader> m_pShader;
//    std::shared_ptr<Texture> mTexture;

    bool m_fMatrixCacheDirty;

private:
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_rotation;
};

#endif //ENGINE_OBJECT_H
