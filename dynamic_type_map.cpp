#include <iostream>
#include <exception>
#include "Dynamic_String.h"
#include "Dynamic_List.h"
#include "Dynamic_Map.h"
#include "Dynamic_Object_Builder.h"

std::string manual_construct_object_json() {
    Dynamic_Map my_map;
    Dynamic_Map my_map2;
    Dynamic_List mylist1;
    Dynamic_List mylist2;
    Dynamic_List mylist3;
    Dynamic_List mylist4;
    my_map.insert("k1", Dynamic_String("my_value"));
    my_map2.insert("k2", Dynamic_String("my_value"));
    my_map.insert("m1", my_map2);
    my_map.insert("m2", my_map2);
    mylist1.push_back(Dynamic_String("list1 ele1"));
    mylist1.push_back(Dynamic_String("list1 ele2"));
    mylist2 = mylist1;
    mylist2.push_back(Dynamic_Int(1000));
    mylist2.push_back(Dynamic_Double(3.14));
    my_map.insert("mylist", mylist1);
    my_map.insert("mylist3", mylist1);
    my_map.insert("mylist2", mylist2);
    mylist3 = std::move(mylist1);
    mylist3.pop_back();
    my_map.insert("empty", mylist1);
    my_map.insert("oriList1", mylist3);
    my_map.erase("mylist");

    mylist4.push_back(my_map2);
    auto& ref_map = mylist4.push_back(Dynamic_Map());
    dynamic_cast<Dynamic_Map *>(&ref_map)->insert("ref_insert", Dynamic_Double(1 / 3.0f));
    my_map2.insert("k3", Dynamic_String("k3 value"));
    mylist4.push_back(std::move(my_map2));
    my_map.insert("mylist4", std::move(mylist4));
    return my_map.str();
}

int main() {
    try {
        auto str = manual_construct_object_json();
        std::cout << "original     string:" << str << std::endl << std::endl;
        Dynamic_Object_Builder object_builder;
        std::unique_ptr<Generic_Value> root(object_builder.build(str));
        std::unique_ptr<Generic_Value> clone(root->clone());
        std::cout << "reconstruct string1:" << root->str() << std::endl << std::endl;
        std::cout << "reconstruct string2:" << clone->str() << std::endl << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Caught: " << e.what() << std::endl; 
    }; 
    return 0;
}

