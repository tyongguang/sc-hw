#include <iostream>
#include "Dynamic_String.h"
#include "Dynamic_List.h"
#include "Dynamic_Map.h"

using std::cout;
using std::endl;

void test_string() {
    Dynamic_Map my_map;
    my_map.insert("my_key", new Dynamic_String("my_value"));
    Generic_Value *p = &my_map;
    cout << p->to_string() << endl;
}

void test_map() {
    Dynamic_Map my_map;

    Dynamic_Map *inner_map = new Dynamic_Map();
    inner_map->insert("inner_key",new Dynamic_String("inner_value"));

    my_map.insert("my_key", inner_map);
    Generic_Value *p = &my_map;
    cout << p->to_string() << endl;
}

void test_list() {
    Dynamic_Map my_map;

    Dynamic_List *inner_lst = new Dynamic_List();
    inner_lst->push_back(new Dynamic_String("string_val"));

    Dynamic_List *lst_in_lst = new Dynamic_List();
    lst_in_lst->push_back(new Dynamic_String("string_val1"));
    lst_in_lst->push_back(new Dynamic_String("string_val2"));
    inner_lst->push_back(lst_in_lst);

    Dynamic_Map *map_in_lst = new Dynamic_Map();
    map_in_lst->insert("key", new Dynamic_String("string_in_map"));
    inner_lst->push_back(map_in_lst);

    my_map.insert("my_key", inner_lst);
    Generic_Value *p = &my_map;
    cout << p->to_string() << endl;
}

int main() {
    test_string();
    test_list();
    test_map();
    return 0;
}

