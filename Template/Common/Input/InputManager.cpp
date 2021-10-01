/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: InputManager.cpp
Purpose: Source of InputManager
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#include "InputManager.h"

void InputManager::Init() {
}

void InputManager::Update() {
    mOldKeyBuffer = mNewKeyBuffer;
}

void InputManager::CleanUp() {
}

bool InputManager::IsPressed(GLint KeyCode) {
    const auto keyIdx = static_cast<int>(KeyCode);
    return !mOldKeyBuffer[keyIdx] && mNewKeyBuffer[keyIdx];
}

bool InputManager::IsReleased(GLint KeyCode) {
    const auto keyIdx = static_cast<int>(KeyCode);
    return !mNewKeyBuffer[keyIdx] && mOldKeyBuffer[keyIdx];
}

bool InputManager::OnKeyDown(GLint KeyCode) {
    return mNewKeyBuffer[static_cast<int>(KeyCode)];
}

void InputManager::on_key_pressed(GLint KeyCode) {
    mNewKeyBuffer[static_cast<int>(KeyCode)] = true;
}

void InputManager::on_key_released(GLint KeyCode) {
    mNewKeyBuffer[static_cast<int>(KeyCode)] = false;
}

