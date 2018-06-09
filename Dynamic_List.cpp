#include "Dynamic_List.h"
#include <sstream>

Dynamic_List::Dynamic_List() {
}

Dynamic_List::Dynamic_List(const Dynamic_List& lst)
    : lst_(lst.lst_) {
}

Dynamic_List::Dynamic_List(Dynamic_List&& lst) 
    : lst_(lst.lst_) {
}

Dynamic_List& Dynamic_List::operator=(const Dynamic_List& src) {
    dynamic_cast<Dynamic_List *>(src.clone())->lst_.swap(lst_);
    return *this;
}

Dynamic_List& Dynamic_List::operator=(Dynamic_List&& src) {
    dynamic_cast<Dynamic_List *>(src.move_clone())->lst_.swap(lst_);
    return *this;
}

Dynamic_List::~Dynamic_List() {
    for (auto iter = lst_.begin(); iter != lst_.end(); ++iter) {
        delete (*iter);
    }
}

void Dynamic_List::push_back(const Generic_Value& val) {
    std::lock_guard<std::mutex> lock(lst_mutex);
    lst_.push_back(val.clone());
}

void Dynamic_List::push_back(Generic_Value&& val) {
    std::lock_guard<std::mutex> lock(lst_mutex);
    lst_.push_back(val.move_clone());
}

void Dynamic_List::pop_back() {
    std::lock_guard<std::mutex> lock(lst_mutex);
    if (lst_.empty()) {
        throw std::runtime_error("The list is empty");
    }
    lst_.pop_back();
}

Generic_Value& Dynamic_List::back() {
    std::lock_guard<std::mutex> lock(lst_mutex);
    if (lst_.empty()) 
        throw std::runtime_error("the list is empty");
    return *lst_.back();
}

std::string Dynamic_List::str() {
    std::lock_guard<std::mutex> lock(lst_mutex);
    std::stringstream ss;
    ss << "[";
    if (lst_.size() > 0) {
        ss << lst_.front()->str();
        for (auto iter = ++lst_.begin(); iter != lst_.end(); ++iter) {
            ss << ", " << (*iter)->str();
        }
    }
    ss << "]";
    return ss.str();
}

Generic_Value* Dynamic_List::clone() const {
    Dynamic_List* p = new Dynamic_List();
    for (auto& item : lst_) {
        p->lst_.push_back(item->clone());
    }
    return p;
}

Generic_Value* Dynamic_List::move_clone() {
    Dynamic_List* p = new Dynamic_List();
    p->lst_ = std::move(this->lst_);
    return p;
}

