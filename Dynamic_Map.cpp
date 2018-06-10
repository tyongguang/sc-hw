#include "Dynamic_Map.h"
#include <mutex>
#include <sstream>
Dynamic_Map::Dynamic_Map() {
}

Dynamic_Map::Dynamic_Map(const Dynamic_Map& m) {
    for (auto& item : m.m_) {
        m_[item.first] = item.second->clone();
    }
}

Dynamic_Map::Dynamic_Map(Dynamic_Map&& m)
    : m_(m.m_) {
}

Dynamic_Map::~Dynamic_Map() {
    for(auto iter = m_.begin(); iter != m_.end(); ++iter) {
        delete (iter->second);
    }
    m_.clear();
}

Generic_Value& Dynamic_Map::insert(const std::string& key,
                        const Generic_Value& val) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto p = val.clone();
    m_[key] = p;
    return *p;
}

Generic_Value& Dynamic_Map::insert(const std::string& key,
    Generic_Value&& val) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto p = val.move_clone();
    m_[key] = p;
    return *p;
}

void Dynamic_Map::erase(const std::string& key) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = m_.find(key);
    if (iter == m_.end()) {
        throw std::runtime_error("The key: " + key + 
                " doesn't exist in the map.");
    }
    delete iter->second;
    m_.erase(iter);
}

Generic_Value& Dynamic_Map::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = m_.find(key);
    if (iter == m_.end()) {
        throw std::runtime_error("The key: " + key + 
            " doesn't exist in the map.");
    }
    return *iter->second;
}

std::string Dynamic_Map::str() {
    std::lock_guard<std::mutex> lock(mutex_);
    std::stringstream ss;
    ss << "{";
    if (m_.size() > 0) {
        ss << "\"" << m_.begin()->first << "\":" << m_.begin()->second->str();
        for (auto iter = ++m_.begin(); iter != m_.end(); ++iter) {
            ss << "," << "\"" << iter->first << "\":" << iter->second->str();
        }
    }
    ss << "}";
    return ss.str();
}

Generic_Value* Dynamic_Map::clone() const {
    Dynamic_Map* p = new Dynamic_Map();
    for (auto& item : m_) {
        p->m_[item.first] = item.second->clone();
    }
    return p;
}

Generic_Value* Dynamic_Map::move_clone() {
    std::lock_guard<std::mutex> lock(mutex_);
    Dynamic_Map* p = new Dynamic_Map();
    p->m_ = std::move(this->m_);
    return p;
}
