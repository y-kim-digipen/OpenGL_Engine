//
// Created by yoonki on 9/14/21.
//

#include "GUIManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void GUI_Manager::Init(GLFWwindow *m_pWindow) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

//    float highDPIscaleFactor = 1.3f;
    ImGuiStyle &style = ImGui::GetStyle();

    style.GrabRounding                           = style.FrameRounding = 2.3f;

    io.Fonts->AddFontFromFileTTF("../../External/Font/Meera-Regular.ttf", 25.0f, NULL, NULL);

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void GUI_Manager::Update() {
    PreRender();
    Render();
    PostRender();
}

void GUI_Manager::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI_Manager::PreRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if(show_demo_window){
        ImGui::ShowDemoWindow(&show_demo_window);
    }
}

void GUI_Manager::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI_Manager::PostRender() {

}

