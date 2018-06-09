#include "Dynamic_String.h"
#include <iostream>

Dynamic_String::Dynamic_String(){}
    
Dynamic_String::Dynamic_String(std::string _s) : s(_s) {}

Dynamic_String::~Dynamic_String() {
	// std::cout << "in Dynamic_String destructor" << std::endl;
}

void Dynamic_String::set(const std::string& val) {
    std::lock_guard<std::mutex> lock(str_mutex);
    s = val;
}

std::string Dynamic_String::get_str() {
    std::lock_guard<std::mutex> lock(str_mutex);
    return s;
}

std::string Dynamic_String::to_string() {
    std::lock_guard<std::mutex> lock(str_mutex);
    return s;
}