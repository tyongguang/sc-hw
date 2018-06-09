#include "Dynamic_String.h"
#include <iostream>



Dynamic_String::Dynamic_String(const char * s) {
    std::lock_guard<std::mutex> lock(mutex_);
    value_ = s;
}

std::string Dynamic_String::str() {
    std::lock_guard<std::mutex> lock(mutex_);
    return "\"" + value_ + "\"";
}

Generic_Value* Dynamic_String::clone() const {
    auto p = new Dynamic_String();
    p->value_ = this->value_;
    return p;
}

Generic_Value * Dynamic_String::move_clone() {
    auto p = new Dynamic_String();
    p->value_ = std::move(this->value_);
    return p;
}
