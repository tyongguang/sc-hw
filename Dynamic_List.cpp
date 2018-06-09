#include "Dynamic_List.h"
#include <iostream>
Dynamic_List::Dynamic_List() {}
Dynamic_List::~Dynamic_List() {
    std::lock_guard<std::mutex> lock(lst_mutex);
    lst.clear();
}

void Dynamic_List::push_back(Generic_Value *val) {
    std::lock_guard<std::mutex> lock(lst_mutex);
    lst.push_back(val);
}

void Dynamic_List::pop_back() {
    std::lock_guard<std::mutex> lock(lst_mutex);
    if (lst.empty()) {
        throw std::runtime_error("The list is empty");
    }
    delete lst.back();
    lst.pop_back();
}

Generic_Value *Dynamic_List::back() {
    std::lock_guard<std::mutex> lock(lst_mutex);
    if (lst.empty()) 
        throw std::runtime_error("the list is empty");
    return lst.back();
}

std::string Dynamic_List::to_string() {
    std::lock_guard<std::mutex> lock(lst_mutex);
    std::string res = "[";
    for (const auto& each_ele : lst) {
        res += each_ele->to_string() + ",";
    }
    if (!lst.empty()) res.pop_back();
    return res + "]";
}