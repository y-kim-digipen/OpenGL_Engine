//
// Created by yoonki on 9/10/21.
//
#include "Engine.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Input/InputManager.h"
//todo delete this after testing scene
#include "TestScene.h"
#include "OBJReader.h"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwWindowHint(GLFW_SAMPLES, 1); // change for anti-aliasing
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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
    OBJReader objReader;
    mFocusedSceneIdx = -1;
    InputManager::Init();
    mGUIManager.Init(m_pWindow);

    SetupShaders();
    SetupMeshes();
    //todo for now, it is for debugging

    SetupScenes();
    mFocusedSceneIdx = 0;
    SetClearColor(Color(0.5f));
    //debug part ended here

    for(auto& scene : m_pScenes){
        scene->Init();
    }

    std::cout << "Engine is initialized, ready to update" << std::endl;
}

void Engine::Update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    InputManager::Update();

    if(mFocusedSceneIdx >= 0){
        PreRender();
        Render();
        PostRender();
    }

    mGUIManager.Update();

    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
}

void Engine::CleanUp() {
    //delete GetInstance();
    mGUIManager.CleanUp();
    for(auto pScene : m_pScenes){
        pScene->CleanUp();
        delete pScene;
        pScene = nullptr;
    }
    glfwTerminate();
}

std::shared_ptr<Mesh> Engine::GetMesh(const std::string &meshStr) {
    return mMeshManager.GetComponent(meshStr);
}

std::shared_ptr<Shader> Engine::GetShader(const std::string &shaderStr) {
    return mShaderManager.GetComponent(shaderStr);;
}

bool Engine::IsRunning() {
    //todo change glfwGetKey to my Input system
    return glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
    glfwWindowShouldClose(m_pWindow) == 0;
}

void Engine::PreRender() {
    m_pScenes[mFocusedSceneIdx]->PreRender();
}

void Engine::Render() {
    m_pScenes[mFocusedSceneIdx]->Render();
}

void Engine::PostRender() {
    m_pScenes[mFocusedSceneIdx]->PostRender();
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
        InputManager::on_key_pressed(key);
    }
    else if (GLFW_REPEAT == action)
    {

    }
    else if (GLFW_RELEASE == action)
    {
        InputManager::on_key_released(key);
    }
}

glm::vec2 Engine::GetWindowSize() {
    return mWinSize;
}

void Engine::SetupScenes() {
    SceneBase* baseScene = new TestScene();
    baseScene->AddCamera();
    m_pScenes.emplace_back(baseScene);
}

void Engine::SetupShaders() {
    auto pShader = mShaderManager.AddComponent("TestShader", new Shader());

    pShader->CreateProgramAndLoadCompileAttachLinkShaders({
                                                                  {GL_VERTEX_SHADER,"../shaders/QuadVertexShader.vert"},
                                                                  {GL_FRAGMENT_SHADER,"../shaders/QuadFragmentShader.frag"} });

    pShader = mShaderManager.AddComponent("3D_DefaultShader", new Shader());

    pShader->CreateProgramAndLoadCompileAttachLinkShaders({
                                                                  {GL_VERTEX_SHADER,"../shaders/SimpleVertexShader.vert"},
                                                                  {GL_FRAGMENT_SHADER,"../shaders/SimpleFragmentShader.frag"} });

    pShader = mShaderManager.AddComponent("DiffuseShader", new Shader());

    pShader->CreateProgramAndLoadCompileAttachLinkShaders({
                                                                  {GL_VERTEX_SHADER,"../shaders/DiffuseShader.vert"},
                                                                  {GL_FRAGMENT_SHADER,"../shaders/DiffuseShader.frag"} });
}

void Engine::SetupMeshes() {
    OBJReader objReader;

    Mesh quadMesh;
    quadMesh.SetDrawType(Mesh::DrawType::TRIANGLES);

    auto pMesh = mMeshManager.AddComponent("TestMesh", quadMesh);
//    pMesh->SetDrawType(GL_TRIANGLES);
    pMesh->initData();
    objReader.ReadOBJFile("../models/bunny.obj", pMesh.get());
    pMesh->SetupBuffer();

//    Mesh cubeMesh;
//    quadMesh.SetDrawType(Mesh::DrawType::TRIANGLES);
//    pMesh = mMeshManager.AddComponent("CubeMesh", cubeMesh);
//    objReader.ReadOBJFile("../models/cube.obj", pMesh.get());
//    pMesh->SetupBuffer();
}

SceneBase* Engine::GetCurrentScene() {
    return m_pScenes[mFocusedSceneIdx];
}








