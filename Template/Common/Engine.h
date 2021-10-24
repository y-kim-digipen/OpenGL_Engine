//
// Created by yoonki on 9/10/21.
//

#ifndef SIMPLE_SCENE_ENGINE_H
#define SIMPLE_SCENE_ENGINE_H

#endif //SIMPLE_SCENE_ENGINE_H

#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <vector>
#include <ObjectComponents/ComponentManager.h>
#include <GL/glew.h>


#include "GUI/GUIManager.h"

#include "Color.h"
#include "Mesh.h"
#include "SceneBase.h"
#include "Shader.h"
#include "VAOManager.h"
#include "VBOManager.h"
#include "UBO.h"

constexpr int ENGINE_SUPPORT_MAX_LIGHTS = 10;

class GLFWwindow;

class Engine
{
public:
    Engine();

    //todo check it is useful, if not delete this function
    //static Engine* GetInstance();
    static int InitWindow(glm::vec2 win_size, const std::string& title_name);

    //Initializing engine features except windows
    static void InitEngine();
    static void Update();
    static void CleanUp();

    static void SetClearColor(Color newClearColor);

    static bool IsRunning();

    static glm::vec2 GetWindowSize();

    static std::shared_ptr<Mesh> GetMesh(const std::string& meshStr);
    static std::shared_ptr<Shader> GetShader(const std::string& shaderStr);
    static GUI::GUI_Manager& GetGUIManager();
    static ComponentManager<Mesh>& GetMeshManager();
    static ComponentManager<Shader>& GetShaderManager();

    static VAOManager& GetVAOManager();
    static VBOManager& GetVBOManager();

    static SceneBase* GetCurrentScene();
    static std::string GetTitleName();
    static float GetFPS();
private:
    static void PreRender();
    static void Render();
    static void PostRender();

    static void SetupScenes();
    static void SetupShaders();
    static void SetupMeshes();
    static void SetupGUI();

    static void GLFWErrorCallback(int, const char* err_str);
    static void KeyboardInputCallback(GLFWwindow*, int key, [[maybe_unused]] int keyCode, int action, [[maybe_unused]] int modifier);
    //static void MouseButtonCallback(GLFWwindow*, int button, int action, [[maybe_unused]] int modifier);
    //static void MouseScrollCallback(GLFWwindow*, double, double yOffset)

private:
    inline static std::string mTitleStr;
    inline static GLFWwindow* m_pWindow;
    inline static glm::vec2 mWinSize;
    inline static Color mClearColor;

    inline static std::vector<SceneBase*> m_pScenes;

    inline static short mFocusedSceneIdx;

    inline static ComponentManager<Mesh> mMeshManager;
    inline static ComponentManager<Shader> mShaderManager;

    inline static VAOManager mVAOManager;
    inline static VBOManager mVBOManager;

    inline static GUI::GUI_Manager mGUIManager;
    inline static float FPS;

    inline static int TargetFPS = 30;

    inline static UBO lightUBO;
};
