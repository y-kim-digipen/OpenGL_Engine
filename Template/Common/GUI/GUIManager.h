//
// Created by yoonki on 9/14/21.
//

#ifndef ENGINE_GUIMANAGER_H
#define ENGINE_GUIMANAGER_H
class GLFWwindow;

class GUI_Manager{
public:
    void Init(GLFWwindow* m_pWindow);
    void Update();
    void CleanUp();

private:
    void PreRender();
    void Render();
    void PostRender();

    bool show_demo_window = true;
};
#endif //ENGINE_GUIMANAGER_H
