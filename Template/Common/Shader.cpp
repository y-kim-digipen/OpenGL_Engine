#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "Shader.h"

void Shader::deleteProgram()
{
    if (mProgramID > 0)
    {
        std::cerr << "PID: " << mProgramID << " shader program deleted" << std::endl;
        glDeleteProgram(mProgramID);
        mProgramID = -1;
    }
}

Shader::~Shader()
{
//    deleteProgram();
}

bool Shader::CreateProgramAndLoadCompileAttachLinkShaders(const std::vector<std::pair<unsigned int, std::string>>& shaderTypePathPairs, bool linkWithGUI)
{
    mProgramID = glCreateProgram();

    if (mProgramID == 0)
    {
        std::cerr<< "Couldn't create shader!" <<std::endl;
        return false;
    }

    int i = 0;
    for (auto typePathPair : shaderTypePathPairs)
    {
        std::ifstream shaderFile(typePathPair.second, std::ifstream::in);
        if (!shaderFile)
        {
            std::cerr << "Unable to find " << typePathPair.second << std::endl;
            deleteProgram();
            return false;
        }
        std::stringstream buffer;
        buffer << shaderFile.rdbuf();
        shaderFile.close();

        unsigned int shaderID = glCreateShader(typePathPair.first);
        std::string shaderSource = buffer.str();
        const char* shaderSourceStr = shaderSource.c_str();
        glShaderSource(shaderID, 1, &shaderSourceStr, NULL);
        glCompileShader(shaderID);

        //check compile status
        int compileResult;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
        if (compileResult == GL_FALSE)
        {
            std::cerr << typePathPair.second << " shader failed to compile!" << std::endl;
            int logLength;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0)
            {
                char* logContent;
                logContent = new char[logLength];
                int writtenLogLength;
                glGetShaderInfoLog(shaderID, logLength, &writtenLogLength, logContent);
                std::cerr << "================Error Message================\n\t"<<logContent << std::endl;
                delete[] logContent;
            }
            deleteProgram();
            return false;
        }
        i++;
        glAttachShader(mProgramID, shaderID);
        if(typePathPair.first == GL_TESS_CONTROL_SHADER || typePathPair.first == GL_TESS_EVALUATION_SHADER)
        {
            mUsingTessellation = true;
        }
        glDeleteShader(shaderID);
    }

    glLinkProgram(mProgramID);
    int linkStatus;
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        std::cout << "program failed to link!" << std::endl;
        int logLength;
        glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0)
        {
            char* logContent;
            logContent = new char[logLength];
            int writtenLogLength;
            glGetProgramInfoLog(mProgramID, logLength, &writtenLogLength, logContent);
            std::cout << logContent <<std::endl;
            delete[] logContent;
        }
        deleteProgram();
        return false;
    }

    m_current_shader_paths = shaderTypePathPairs;

    GLint count;
    glGetProgramiv(mProgramID, GL_ACTIVE_ATTRIBUTES, &count);
    printf("\tActive Attributes: %d\n", count);

    const GLint numShaderAttribs = static_cast<GLint>(ShaderAttribNames.size());

    for (GLint i = 0; i < count; i++)
    {
        const GLsizei bufSize = 16; // maximum name length
        GLchar name[bufSize]; // variable name in GLSL
        GLsizei length; // name length

        GLint size; // size of the variable
        GLenum type; // type of the variable (float, vec3 or mat4, etc)

        glGetActiveAttrib(mProgramID, (GLuint)i, bufSize, &length, &size, &type, name);

        printf("\t\t -Attribute #%d Name: %s\n", i, name);

        const std::string nameStr = name;
        //todo also check type to check match
        GLint attribIdx = 0;
        for(attribIdx = 0; attribIdx < numShaderAttribs; ++attribIdx){
            if(ShaderAttribNames[attribIdx] == nameStr){
                mShaderAttributeUsages[attribIdx] = true;
            }
        }
        if(attribIdx > numShaderAttribs){
            std::cerr << "Trying to using unsupported shader attrib :" << name << std::endl;
        }

    }

    UnUse();

    if(!linkWithGUI)
    {
        return true;
    }

    Use();

    GLint numActiveUniforms = 0;
    GLuint curOffset = 0;
    glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

    mUniformVarBuffer.resize(2048);

    Byte* curUniformBufferLocation = mUniformVarBuffer.data();

    for (GLint idx = 0; idx < numActiveUniforms; idx++)
    {
        std::string uniformVarName;
        uniformVarName.resize(256);
        GLsizei actualLength;
        GLenum uniformType = 0;
        GLint uniformArraySize = 0;

        glGetActiveUniform(mProgramID, idx, static_cast<GLsizei>(uniformVarName.length()), &actualLength, &uniformArraySize, &uniformType,uniformVarName.data());
        uniformVarName.resize(actualLength);

        UniformAttribute currentUniformAttribute;
        currentUniformAttribute.mOffset = curOffset;
        currentUniformAttribute.mType = static_cast<DataType>(uniformType);

        GLsizei dataTypeSize = 0;

        GLint curUniformProgramLocation = glGetUniformLocation(mProgramID, uniformVarName.c_str());

        switch (currentUniformAttribute.mType)
        {
            case DataType::Bool:
            {
                dataTypeSize = sizeof(GLboolean);
                GLint defaultValue = GLboolean();
                glGetUniformiv(mProgramID, curUniformProgramLocation, &defaultValue);
                new (curUniformBufferLocation) GLboolean(static_cast<GLboolean>(defaultValue));
                break;
            }
            case DataType::Int:
            {
                dataTypeSize = sizeof(GLint);
                GLint defaultValue = GLint();
                glGetUniformiv(mProgramID, curUniformProgramLocation, &defaultValue);
                new (curUniformBufferLocation) GLint(defaultValue);
                break;
            }
            case DataType::Float:
            {
                dataTypeSize = sizeof(GLfloat);
                GLfloat defaultValue = GLfloat();
                glGetUniformfv(mProgramID, curUniformProgramLocation, &defaultValue);
                new (curUniformBufferLocation) GLfloat(defaultValue);
                break;
            }
            case DataType::Vec2f:
            {
                dataTypeSize = sizeof(glm::vec2);
                glm::vec2 defaultValue = glm::vec2();
                glGetnUniformfv(mProgramID, curUniformProgramLocation, dataTypeSize, &defaultValue.x);
                new (curUniformBufferLocation) glm::vec2(defaultValue);
                break;
            }
            case DataType::Vec3f:
            {
                dataTypeSize = sizeof(glm::vec3);
                glm::vec3 defaultValue = glm::vec3();
                glGetnUniformfv(mProgramID, curUniformProgramLocation, dataTypeSize, &defaultValue.x);
                new (curUniformBufferLocation) glm::vec3(defaultValue);
                break;
            }
            case DataType::Vec4f:
            {
                dataTypeSize = sizeof(glm::vec4);
                glm::vec4 defaultValue = glm::vec4();
                glGetnUniformfv(mProgramID, curUniformProgramLocation, dataTypeSize, &defaultValue.x);
                new (curUniformBufferLocation) glm::vec4(defaultValue);
                break;
            }
            case DataType::Mat3f:
            {
                dataTypeSize = sizeof(glm::mat3);
                glm::mat3 defaultValue = glm::mat3();
                glGetnUniformfv(mProgramID, curUniformProgramLocation, dataTypeSize, &defaultValue[0].x);
                new (curUniformBufferLocation) glm::mat3(defaultValue);
                break;
            }
            case DataType::Mat4f:
            {
                dataTypeSize = sizeof(glm::mat4);
                glm::mat4 defaultValue = glm::mat4();
                glGetnUniformfv(mProgramID, curUniformProgramLocation, dataTypeSize, &defaultValue[0].x);
                new (curUniformBufferLocation) glm::mat4(defaultValue);
                break;
            }
            default:
            {
                /*throw std::runtime_error("Unknown Type");*/

                break;
            }
        }
        mUniforms.emplace(uniformVarName, currentUniformAttribute);
        curOffset += dataTypeSize * uniformArraySize;
        curUniformBufferLocation = mUniformVarBuffer.data() + curOffset;
    }
    mUniformVarBuffer.resize(curOffset);
    UnUse();
    return true;
}

void Shader::Use() const
{
    if (mProgramID == 0)
    {
        std::cout<< "Shader program handle is invalid!" << std::endl;
    }
    glUseProgram(mProgramID);
}

void Shader::UnUse() const
{
    glUseProgram(0);
}

void Shader::SetUniform1b(char const* name, bool val)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable " << name << "not found!" << std::endl;
        std::exit(-1);
    }
    glUniform1i(location, val);
}

void Shader::SetUniform1i(char const* name, int val)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable " << name << " not found!" << std::endl;
        std::exit(-1);
    }
    glUniform1i(location, val);
}

void Shader::SetUniform1f(char const* name, float val)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable "<< name << " not found!";
        std::exit(-1);
    }
    glUniform1f(location, val);
}

void Shader::SetUniformVec2f(char const* name, float x, float y)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable " << name << " not found!" << std::endl;
        std::exit(-1);
    }
    glUniform2f(location, x, y);
}

void Shader::SetUniformVec2f(char const* name, const glm::vec2& v)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable " << name << " not found!" << std::endl;
        std::exit(-1);
    }
    glUniform2f(location, v.x, v.y);
}

void Shader::SetUniformVec3f(char const* name, float x, float y, float z)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable " << name << " not found!" << std::endl;
        std::exit(-1);
    }
    glUniform3f(location, x, y, z);
}

void Shader::SetUniformVec3f(char const* name, const glm::vec3& v)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable " << name << " not found!" << std::endl;
        std::exit(-1);
    }
    glUniform3f(location, v.x, v.y, v.z);
}

void Shader::SetUniformVec4f(char const* name, const glm::vec4& v)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable " << name << " not found!" <<std::endl;
        std::exit(-1);
    }
    glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shader::SetUniformMatrix3f(char const* name, glm::mat3& m)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location < 0)
    {
        std::cout << "Uniform variable " << name << " not found!"<< std::endl;
        std::exit(-1);
    }
    glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
}

void Shader::SetUniformMatrix4f(char const* name, glm::mat4& m)
{
    GLint location = glGetUniformLocation(mProgramID, name);
    if(location < 0)
    {
        std::cout << "Uniform variable " << name << " not found!" << std::endl;
        std::exit(-1);
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void Shader::SetAllUniforms()
{
    for(auto& uniformAttrib : mUniforms)
    {
        const std::string& name = uniformAttrib.first;
        switch(uniformAttrib.second.mType)
        {
            case DataType::Bool:
            {
                SetUniform1b(name.c_str(), GetUniformValue<GLboolean>(name));
                break;
            }
            case DataType::Int:
            {
                SetUniform1i(name.c_str(), GetUniformValue<GLint>(name));
                break;
            }
            case DataType::Float:
            {
                SetUniform1f(name.c_str(), GetUniformValue<GLfloat>(name));
                break;
            }
            case DataType::Vec2f:
            {
                SetUniformVec2f(name.c_str(), GetUniformValue<glm::vec2>(name));
                break;
            }
            case DataType::Vec3f:
            {
                SetUniformVec3f(name.c_str(), GetUniformValue<glm::vec3>(name));
                break;
            }
            case DataType::Vec4f:
            {
                SetUniformVec4f(name.c_str(), GetUniformValue<glm::vec4>(name));
                break;
            }
            case DataType::Mat3f:
            {
                SetUniformMatrix3f(name.c_str(), GetUniformValue<glm::mat3>(name));
                break;
            }
            case DataType::Mat4f:
            {
                SetUniformMatrix4f(name.c_str(), GetUniformValue<glm::mat4>(name));
                break;
            }
            default:
            {
                /*throw "Logic error";*/
                break;
            }
        }
    }
}

void Shader::Reload()
{
    CreateProgramAndLoadCompileAttachLinkShaders(m_current_shader_paths);
}

Shader::Shader(const Shader &other) {
    std::cerr << "Refer copy constructor called" << std::endl;
}

Shader::Shader(Shader &&other) {
    std::cerr << "RRef called" << std::endl;
    mProgramID = other.mProgramID;
    other.mProgramID = -1;
    m_current_shader_paths = std::move(other.m_current_shader_paths);
    mUniformVarBuffer = std::move(other.mUniformVarBuffer);
    mUniforms = std::move(other.mUniforms);
    mUsingTessellation = other.mUsingTessellation;
    mShaderAttributeUsages = other.mShaderAttributeUsages;

//    CreateProgramAndLoadCompileAttachLinkShaders(other.m_current_shader_paths, !other.mUniforms.empty());
}

Shader &Shader::operator=(const Shader &other) {
    std::cerr << "Refer copy called" << std::endl;
    return *this;
}

Shader &Shader::operator=(Shader &&other) {
    std::cerr << "rRefer copy called" << std::endl;
    return *this;
}

const std::array<bool, 4> &Shader::GetAttribUsages() const {
    return mShaderAttributeUsages;
}

