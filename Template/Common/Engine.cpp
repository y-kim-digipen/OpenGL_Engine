//
// Created by yoonki on 9/10/21.
//
#include "Engine.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Input/InputManager.h"
Engine::Engine() {
    mClearColor = Color(0.f);
    mWinSize = glm::vec2{};
}

//Engine* Engine::GetInstance(){
//    static Engine* p_instance = nullptr;
//    if(p_instance == nullptr){
//        p_instance = new Engine();
//    }
//    return p_instance;
//}

int Engine::InitWindow(glm::vec2 win_size, const std::string& title_name) {
    mWinSize = win_size;

    //GLFW settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    glfwWindowHint(GLFW_SAMPLES, 1); // change for anti-aliasing
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    glfwInit();

    m_pWindow = glfwCreateWindow(static_cast<int>(mWinSize.x), static_cast<int>(mWinSize.y), title_name.c_str(), nullptr, nullptr);
    if(m_pWindow == nullptr) {
        std::cerr << "Failed to open GLFW window. Check if your GPU is compatible." << std::endl;
        glfwTerminate();
        return -1;
    }
    //Set up callback functions
    glfwSetErrorCallback(&Engine::GLFWErrorCallback);
    glfwSetKeyCallback(m_pWindow, &Engine::KeyboardInputCallback);

    // OpenGL resource model - "glfwCreateWindow" creates the necessary data storage for the OpenGL
    // context but does NOT make the created context "current". We MUST make it current with the following
    // call
    glfwMakeContextCurrent(m_pWindow);

    // Initialize GLEW
    glewExperimental = static_cast<GLboolean>(true); // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW." << std::endl;
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(m_pWindow, GLFW_STICKY_KEYS, GL_TRUE);

    return 0;
}

void Engine::SetClearColor(Color newClearColor) {
    mClearColor = newClearColor;
    glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
}

void Engine::InitEngine() {
    InputManager::Init();
}

void Engine::Update() {
    PreRender();
    Render();
    PostRender();

    //todo delete this after scene is implemented
    glfwSwapBuffers(m_pWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();


}

void Engine::CleanUp() {
    //delete GetInstance();
    glfwTerminate();
}

bool Engine::IsRunning() {
    //todo change glfwGetKey to my Input system
    return glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
    glfwWindowShouldClose(m_pWindow) == 0;
}

void Engine::PreRender() {

}

void Engine::Render() {

}

void Engine::PostRender() {

}

void Engine::GLFWErrorCallback([[maybe_unused]]int, const char *err_str) {
    std::cerr << "GLFW Error: " << err_str << std::endl;
}

void Engine::KeyboardInputCallback(GLFWwindow *, [[maybe_unused]] int key, int keyCode, int action, [[maybe_unused]] int modifier) {
    if (key < 0 || key > 1000)
    {
        return;
    }

    if (GLFW_PRESS == action)
    {
        InputManager::on_key_pressed(static_cast<Key>(key));
    }
    else if (GLFW_REPEAT == action)
    {

    }
    else if (GLFW_RELEASE == action)
    {
        InputManager::on_key_released(static_cast<Key>(key));
    }
}








