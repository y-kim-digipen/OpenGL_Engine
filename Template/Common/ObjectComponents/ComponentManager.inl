//
// Created by yoonki on 9/11/21.
//
#include <iostream>
#include "ComponentManager.h"

template<typename ComponentType>
ComponentManager<ComponentType>::~ComponentManager() {
    Cleanup();
}


template<typename ComponentType>
void ComponentManager<ComponentType>::Cleanup() {
    //todo have to do something
    mNameList.clear();
//    for(auto& pComp : mComponentMap){
//        pComp.second->release();
//    }
    mComponentMap.clear();
}

template<typename ComponentType>
bool ComponentManager<ComponentType>::validate_existence(const std::string &nameStr) {
    return std::find(mNameList.begin(), mNameList.end(), nameStr) == mNameList.end();
}

template<typename ComponentType>
bool ComponentManager<ComponentType>::RemoveComponent(const std::string &nameStr) {
    if(validate_existence(nameStr) == false){
        return false;
    }
    mNameList.erase(std::find(mNameList.begin(), mNameList.end(), nameStr));
    mComponentMap.erase(nameStr);
    //for debugging purpose
    //todo change to meaningful error message
    if(validate_sizes() == false){
        throw(std::logic_error("????????/"));
    }
    return true;
}

template<typename ComponentType>
bool ComponentManager<ComponentType>::validate_sizes() {
    return mNameList.size() == mNameList.size();
}

template<typename ComponentType>
size_t ComponentManager<ComponentType>::Size() const {
    if(validate_sizes() == false){
        throw(std::logic_error("????????/"));
    }
    return mNameList.size();
}

template<typename ComponentType>
std::shared_ptr<ComponentType> ComponentManager<ComponentType>::AddComponent(const std::string &name, ComponentType &&type) {
    return AddComponent(name, std::make_shared<ComponentType>(type));
}

template<typename ComponentType>
std::shared_ptr<ComponentType> ComponentManager<ComponentType>::AddComponent(const std::string &name, ComponentType *type) {
    return AddComponent(name, std::shared_ptr<ComponentType>(type));
}

template<typename ComponentType>
std::shared_ptr<ComponentType> ComponentManager<ComponentType>::AddComponent(const std::string &name, std::shared_ptr<ComponentType> type) {
    if(validate_existence(name) == false){
        std::cerr << "Failed to add" << name << std::endl;
        return nullptr;
    }
    mNameList.push_back(name);
    std::cout << name << " successfully added" << std::endl;
    return mComponentMap.template try_emplace(name.c_str(), type).first->second;
}

template<typename ComponentType>
template<typename... Args>
std::shared_ptr<ComponentType> ComponentManager<ComponentType>::AddComponent(const std::string &name, Args... args) {
    return AddComponent(name, std::make_shared<ComponentType>(ComponentType(args...)));
}

template<typename ComponentType>
std::shared_ptr<ComponentType> ComponentManager<ComponentType>::GetComponent(const std::string &name) {
    auto foundItr = mComponentMap.template find(name);
    if(foundItr != mComponentMap.end()){
        return foundItr->second;
    }
    return nullptr;
}


//template<typename ComponentType>
//const std::vector<const char *const> &ComponentManager<ComponentType>::ListNames() {
//    return std::copy(mNameList.begin(), mNameList.end());
//}
