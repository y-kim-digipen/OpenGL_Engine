/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: ComponentManager.h
Purpose: Header of ComponentManager
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#ifndef ENGINE_COMPONENTMANAGER_H
#define ENGINE_COMPONENTMANAGER_H
//todo move unnecessary include to cpp
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

#include "ComponentBase.h"
template<typename ComponentType>
class ComponentManager{
public:
    ~ComponentManager();
    void Cleanup();
//    std::shared_ptr<ComponentType> GetComponent(const std::string& nameStr);
//    bool LoadFromFile(const std::string& fileStr);
    std::shared_ptr<ComponentType> AddComponent(const std::string& name, ComponentType&& type, bool showGUI = true);
    std::shared_ptr<ComponentType> AddComponent(const std::string& name, ComponentType* type, bool showGUI = true);
    std::shared_ptr<ComponentType> AddComponent(const std::string& name, std::shared_ptr<ComponentType> pComponent, bool showGUI = true);
    template<typename... Args>
    std::shared_ptr<ComponentType> AddComponent(const std::string& name, Args... args, bool showGUI = true);
    bool RemoveComponent(const std::string& nameStr);
    std::shared_ptr<ComponentType> GetComponent(const std::string& name);

    [[nodiscard]] size_t Size() const;
    //todo for future expansion
    //    const std::vector<const char* const>& ListNames();
    //virtual bool CopyFromType(const ObjectComponent&& copiedType) = 0;

    const std::vector<std::string>& GetNameList();
protected:
    bool validate_existence(const std::string&);
    bool validate_sizes();

private:
    std::vector<std::string> mNameList;
    std::map<std::string, std::shared_ptr<ComponentType>> mComponentMap;
};


#include "ComponentManager.inl"

#endif //ENGINE_COMPONENTMANAGER_H
