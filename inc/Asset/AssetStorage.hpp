#pragma once

#include <vector>
#include <stack>
#include <memory>
#include <inttypes.h>

#include <Asset/AssetHandle.hpp>
#include <Logger/Logger.hpp>

namespace AMB {

template<typename T>
class AssetStorage {
public:
    ~AssetStorage();

    template<typename ...ARGS>
    AssetHandle add(ARGS&&... args);

    bool remove(AssetHandle handle);

    void remove_all();

    T& get(AssetHandle handle);

    bool validity(AssetHandle handle) const;

private:
    std::vector<std::unique_ptr<T>> m_storage;
    std::stack<int32_t> m_free_id;
};

template<typename T>
AssetStorage<T>::~AssetStorage() {
    remove_all();
}

template<typename T>
template<typename ...ARGS>
AssetHandle AssetStorage<T>::add(ARGS&&... args) {
    AssetHandle handle{-1, typeid(T)};

    if (m_free_id.empty()) {
        handle.index = m_storage.size();
        m_storage.emplace_back(std::make_unique<T>(std::forward<ARGS>(args)...));

    }else{
        handle.index = m_free_id.top();
        m_free_id.pop();
        m_storage[handle.index] = std::make_unique<T>(std::forward<ARGS>(args)...);
    }

    return handle;
}

template<typename T>
bool AssetStorage<T>::remove(AssetHandle handle) {
    // Check if the index refer to an existing object
    if (!validity(handle)) {
        return false;
    }

    // Remove the object
    m_free_id.push(handle.index);
    m_storage[handle.index] = nullptr;

    return true;
}

template<typename T>
void AssetStorage<T>::remove_all() {
    m_storage.clear();
    while (!m_free_id.empty()) {
        m_free_id.pop();
    }
}

template<typename T>
T& AssetStorage<T>::get(AssetHandle handle) {
    return *m_storage[handle.index];
}

template<typename T>
bool AssetStorage<T>::validity(AssetHandle handle) const {
    return handle.type == typeid(T) && handle.index >= 0 && 
        handle.index < (int32_t)m_storage.size() && m_storage[handle.index] != nullptr;
}

}