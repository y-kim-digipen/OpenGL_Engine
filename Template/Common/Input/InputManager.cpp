//
// Created by yoonki on 9/11/21.
//
#include "InputManager.h"

std::vector<bool> InputManager::mNewKeyBuffer, InputManager::mOldKeyBuffer;

void InputManager::Init() {
    mOldKeyBuffer.resize(static_cast<size_t>(Key::COUNT));
    mNewKeyBuffer.resize(static_cast<size_t>(Key::COUNT));
}

void InputManager::Update() {
    mOldKeyBuffer = mNewKeyBuffer;
}

void InputManager::CleanUp() {
    mOldKeyBuffer.clear();
    mNewKeyBuffer.clear();
}

bool InputManager::IsPressed(Key KeyCode) {
    const auto keyIdx = static_cast<short>(KeyCode);
    return !mOldKeyBuffer[keyIdx] && mNewKeyBuffer[keyIdx];
}

bool InputManager::IsReleased(Key KeyCode) {
    const auto keyIdx = static_cast<short>(KeyCode);
    return !mNewKeyBuffer[keyIdx] && mOldKeyBuffer[keyIdx];
}

bool InputManager::OnKeyDown(Key KeyCode) {
    return mNewKeyBuffer[static_cast<short>(KeyCode)];
}

void InputManager::on_key_pressed(Key KeyCode) {
    mNewKeyBuffer[static_cast<short>(KeyCode)] = true;
}

void InputManager::on_key_released(Key KeyCode) {
    mNewKeyBuffer[static_cast<short>(KeyCode)] = false;
}

