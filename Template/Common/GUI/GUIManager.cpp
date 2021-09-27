//
// Created by yoonki on 9/14/21.
//

#include "GUIManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GUIWindow.h"
#include "EngineInfo.h"

namespace GUI {
    void GUI_Manager::Init(GLFWwindow *m_pWindow) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;

//    float highDPIscaleFactor = 1.3f;
        ImGuiStyle &style = ImGui::GetStyle();

        style.GrabRounding = style.FrameRounding = 2.3f;

        io.Fonts->AddFontFromFileTTF("../../External/Font/Meera-Regular.ttf", 25.0f, NULL, NULL);

        ImGui::StyleColorsDark();


        ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
        ImGui_ImplOpenGL3_Init("#version 410");

        m_pWindows.try_emplace("Engine Info Window", new EngineInfo("Engine Info Window"));

        InitWindows();
    }

    void GUI_Manager::Update() {
        PreRender();
        Render();
        PostRender();
    }

    void GUI_Manager::CleanUp() {
        for (auto pWindow: m_pWindows) {
            pWindow.second->CleanUp();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    GUI_Window *GUI_Manager::AddWindow(const std::string &name) {
        auto result = m_pWindows.try_emplace(name, new GUI_Window(name));
        if (!result.second) {
            return nullptr;
        }
        InitWindows();
        return result.first->second;
    }

    bool GUI_Manager::HasWindow(const std::string &window) {
        return m_pWindows.find(window) != m_pWindows.end();
    }

    void GUI_Manager::RemoveWindow(const std::string &windowNameStr) {
        if(!HasWindow(windowNameStr)){
            return;
        }
        delete m_pWindows.find(windowNameStr)->second;
        m_pWindows.erase(windowNameStr);
    }

    void GUI_Manager::PreRender() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GUI_Manager::Render() {
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        for (auto pWindow: m_pWindows) {
            pWindow.second->PreRender();
            pWindow.second->Render();
            pWindow.second->PostRender();
        }
    }

    void GUI_Manager::PostRender() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GUI_Manager::InitWindows() {
        for (auto pWindow: m_pWindows) {
            pWindow.second->Init();
        }
    }




}



