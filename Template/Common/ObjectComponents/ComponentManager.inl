//
// Created by yoonki on 9/11/21.
//
#include "ComponentManager.h"

template<typename ComponentType>
void ComponentManager<ComponentType>::Cleanup() {
    mNameList.clear();
    mComponentMap.clear();
}

template<typename ComponentType>
bool ComponentManager<ComponentType>::validate_existence(const std::string &nameStr) {
    return std::find(mNameList.begin(), mNameList.end(), nameStr) != mNameList.end();
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
bool ComponentManager<ComponentType>::AddComponent(const std::string &name, ComponentType &&type) {
    return AddComponent(name, std::make_shared<ComponentType>(type));
}

template<typename ComponentType>
bool ComponentManager<ComponentType>::AddComponent(const std::string &name, ComponentType *type) {
    return AddComponent(name, std::shared_ptr<ComponentType>(type));
}

template<typename ComponentType>
bool ComponentManager<ComponentType>::AddComponent(const std::string &name, std::shared_ptr<ComponentType> type) {
    if(validate_existence(name) == false){
        return false;
    }
    mNameList.push_back(name);
    mComponentMap.template try_emplace(name.c_str(), type);
    return true;
}

template<typename ComponentType>
template<typename... Args>
bool ComponentManager<ComponentType>::AddComponent(const std::string &name, Args... args) {
    return AddComponent(name, std::make_shared<ComponentType>(ComponentType(args...)));
}

//template<typename ComponentType>
//const std::vector<const char *const> &ComponentManager<ComponentType>::ListNames() {
//    return std::copy(mNameList.begin(), mNameList.end());
//}
