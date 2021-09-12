#ifndef SHADER_HPP
#define SHADER_HPP

#include <map>
#include <vector>

#include <glm/glm.hpp>

#include "CommonConstants.h"

enum Primitive_Enum
{
    TriangleStrip = 0,
    Points,
    LineStrip
};

class Shader
{
public:
    struct UniformAttribute
    {
        GLuint mOffset = 0;
        DataType mType = DataType::Count;
    };

    ~Shader();
    //TODO load
    bool CreateProgramAndLoadCompileAttachLinkShaders(const std::vector<std::pair<unsigned int, std::string>>& shaderTypePathPairs, bool linkWithGUI = true);
    void Use() const;
    void UnUse() const;
    void SetAllUniforms();
    void Reload();
    template<class T>
    T& GetUniformValue(std::string&& name)
    {
        return *(reinterpret_cast<T*>(mUniformVarBuffer.data() + mUniforms[name].mOffset));
    }

    template<class T>
    T& GetUniformValue(const std::string& name)
    {
        return *(reinterpret_cast<T*>(mUniformVarBuffer.data() + mUniforms[name].mOffset));
    }

    auto& GetUniforms() const
    {
        return mUniforms;
    }

    bool HasUniform(std::string&& name) const
    {
        return mUniforms.end() != mUniforms.find(name);
    }

    bool UsingTessellationShader() const
    {
        return mUsingTessellation;
    }

    unsigned int GetProgramID() const { return mProgramID; }

    //TODO
    void SetUniform1b(char const* name, bool val);
    void SetUniform1i(char const* name, int val);
    void SetUniform1f(char const* name, float val);
    void SetUniformVec2f(char const* name, float x, float y);
    void SetUniformVec2f(char const* name, const glm::vec2& v);
    void SetUniformVec3f(char const* name, float x, float y, float z);
    void SetUniformVec3f(char const* name, const glm::vec3& v);
    void SetUniformVec4f(char const* name, const glm::vec4& v);
    void SetUniformMatrix3f(char const* name, glm::mat3& m);
    void SetUniformMatrix4f(char const* name, glm::mat4& m);

private:
    using Byte = unsigned char;

    std::vector<std::pair<unsigned int, std::string>> m_current_shader_paths;
    mutable std::vector<Byte> mUniformVarBuffer;
    mutable std::map<std::string, UniformAttribute> mUniforms;

    unsigned int mProgramID = 0;

    GLboolean mUsingTessellation = false;
    void deleteProgram();
};

#endif
