//
// Created by yoonki on 9/14/21.
//

#ifndef ENGINE_GUIMANAGER_H
#define ENGINE_GUIMANAGER_H
#include <map>
class GLFWwindow;
namespace GUI{
    class GUI_Window;
    class GUI_Manager{
    public:
        void Init(GLFWwindow* m_pWindow);
        void Update();
        void CleanUp();

        GUI_Window* AddWindow(const std::string& name);
        bool HasWindow(const std::string& windowNameStr);
        void RemoveWindow(const std::string& windowNameStr);
    private:
        void InitWindows();
        void PreRender();
        void Render();
        void PostRender();

    private:
        bool show_demo_window = true;
        std::map<std::string, GUI_Window*> m_pWindows;

    };
}
#endif //ENGINE_GUIMANAGER_H
