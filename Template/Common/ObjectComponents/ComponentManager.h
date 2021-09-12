//
// Created by yoonki on 9/11/21.
//
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
    void Cleanup();
//    std::shared_ptr<ComponentType> GetComponent(const std::string& nameStr);
//    bool LoadFromFile(const std::string& fileStr);
    bool AddComponent(const std::string& name, ComponentType&& type);
    bool AddComponent(const std::string& name, ComponentType* type);
    bool AddComponent(const std::string& name, std::shared_ptr<ComponentType> pComponent);
    template<typename... Args>
    bool AddComponent(const std::string& name, Args... args);
    bool RemoveComponent(const std::string& nameStr);


    [[nodiscard]] size_t Size() const;
    //todo for future expansion
    //    const std::vector<const char* const>& ListNames();
    //virtual bool CopyFromType(const ObjectComponent&& copiedType) = 0;

protected:
    bool validate_existence(const std::string&);
    bool validate_sizes();

private:
    std::vector<std::string> mNameList;
    std::map<std::string, std::shared_ptr<ComponentType>> mComponentMap;
};


#include "ComponentManager.inl"

#endif //ENGINE_COMPONENTMANAGER_H
