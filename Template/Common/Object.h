//
// Created by yoonki on 9/12/21.
//

#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

#include <memory>
#include <functional>
//#include <GUI/ObjectDetailContent.h>

#include "Shader.h"
#include "Mesh.h"

namespace GUI{
    class ObjectDetailContent;
}
class Object{
    friend class GUI::ObjectDetailContent;
public:
    Object(const std::string& name);
    Object(const std::string& name, std::shared_ptr<Mesh> pMesh, std::shared_ptr<Shader> pShader);
    Object(const std::string& name, const std::string& meshStr, const std::string& shaderStr);
    void Init();
    virtual void PreRender();
    void Render() const;
    void PostRender();

    void CleanUp() const;
    //todo implement this
    bool SetShader(const std::string& shaderStr);
    bool SetMesh(const std::string& meshStr);

    [[nodiscard]] std::string GetUsingMeshName() const;
    [[nodiscard]] std::string GetUsingShaderName() const;

    [[nodiscard]] bool IsRenderReady() const;

    //Transform settings
    glm::vec3 GetPosition();
    void SetPosition(glm::vec3 position);
    void AddPosition(glm::vec3 amount);

    glm::vec3 GetRotation();
    void SetRotation(glm::vec3 rotation);
    void AddRotation(glm::vec3 amount);

    glm::vec3 GetScale();
    void SetScale(glm::vec3 scale);
    void AddScale(glm::vec3 amount);

    void BindFunction(std::function<void(Object*)> func);

    glm::mat4 GetObjectToWorldMatrix() const;

    std::string GetName() const;
private:
    void TryCalculateMatrix();
    void RenderModel() const;
    void RenderVertexNormal() const;
    void RenderFaceNormal() const;

private:
    std::shared_ptr<Mesh> m_pMesh;
    std::shared_ptr<Shader> m_pShader;
    std::string mObjectName;
    std::string mMeshName;
    std::string mShaderName;
//    std::shared_ptr<Texture> mTexture;

    GLboolean m_MatrixCacheDirty;

    glm::mat4 mToWorldMatrix;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_rotation;

    std::function<void(void)> mAdditionalFunction;

    bool mDoVertexNormalDrawing;
    bool mDoFaceNormalDrawing;
};

#endif //ENGINE_OBJECT_H
