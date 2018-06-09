#include "Dynamic_Map.h"
#include <mutex>
#include <iostream>
Dynamic_Map::Dynamic_Map() {}

Dynamic_Map::~Dynamic_Map() {
    std::lock_guard<std::mutex> lock(map_mutex);
    for(auto itr = m.begin(); itr != m.end(); itr++)
    {
        delete (itr->second);
    }
    m.clear();
}

void Dynamic_Map::insert(const std::string& key, 
                        Generic_Value *val) {
    std::lock_guard<std::mutex> lock(map_mutex);
    m[key] = val;
}

void Dynamic_Map::erase(const std::string& key) {
    std::lock_guard<std::mutex> lock(map_mutex);
    if (m.find(key) == m.end()) {
        throw std::runtime_error("The key: " + key + 
                " doesn't exist in the map.");
    }
    delete m[key];
    m.erase(key);
}

Generic_Value *Dynamic_Map::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(map_mutex);
    if (m.find(key) == m.end()) {
        throw std::runtime_error("The key: " + key + 
            " doesn't exist in the map.");
    }
    return m[key];
}

std::string Dynamic_Map::to_string() {
    std::lock_guard<std::mutex> lock(map_mutex);
    std::string res;
    res += "{";
    for (const auto& each_ele : m) {
        res += each_ele.first + ": " + 
                each_ele.second->to_string() + ",";
    }
    if (!m.empty()) res.pop_back();
    res += "}";
    return res;
}