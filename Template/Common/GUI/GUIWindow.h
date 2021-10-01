//
// Created by yoonki on 9/15/21.
//

#ifndef ENGINE_GUIWINDOW_H
#define ENGINE_GUIWINDOW_H

#include "GUIObject.h"

#include <string>
#include <map>
namespace GUI{
    class GUI_Content;
    class GUI_Window : public GUI_Object{
        friend class GUI_Manager;
    public:
        ~GUI_Window();
        [[nodiscard]] std::string GetTitleName() const;
        bool AddContent(const std::string& name, GUI_Content* content);
        void AddFlag(ImGuiWindowFlags flag);

        void SetCanClose(bool canClose);
    protected:
        bool IsFocused() const;
        void PreRender() override;
        void Render() override;
        void PostRender() override;
    protected:
        explicit GUI_Window(const std::string &titleName);
        std::string mTitleName;
        ImGuiWindowFlags mWindowFlags;
        std::map<std::string, GUI_Content*> m_pContents;

        bool mCanClose = true;
    };
}


#endif //ENGINE_GUIWINDOW_H
