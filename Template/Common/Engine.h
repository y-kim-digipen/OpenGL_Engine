//
// Created by yoonki on 9/10/21.
//

#ifndef SIMPLE_SCENE_ENGINE_H
#define SIMPLE_SCENE_ENGINE_H

#endif //SIMPLE_SCENE_ENGINE_H
#include <string>
#include <glm/glm.hpp>

#include "Color.h"



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
private:
    static void PreRender();
    static void Render();
    static void PostRender();

    static void GLFWErrorCallback(int, const char* err_str);
    static void KeyboardInputCallback(GLFWwindow*, int key, [[maybe_unused]] int keyCode, int action, [[maybe_unused]] int modifier);
    //static void MouseButtonCallback(GLFWwindow*, int button, int action, [[maybe_unused]] int modifier);
    //static void MouseScrollCallback(GLFWwindow*, double, double yOffset)

private:
    inline static GLFWwindow* m_pWindow;
    inline static glm::vec2 mWinSize;
    inline static Color mClearColor;
};
