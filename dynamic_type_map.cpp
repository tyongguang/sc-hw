#include <iostream>
#include "Dynamic_String.h"
#include "Dynamic_List.h"
#include "Dynamic_Map.h"

using std::cout;
using std::endl;

void test_string() {
    Dynamic_Map my_map;
    Dynamic_Map my_map2;
    Dynamic_List mylist1;
    Dynamic_List mylist2;
    Dynamic_List mylist3;
    my_map.insert("k1", Dynamic_String("my_value"));
    my_map2.insert("k2", Dynamic_String("my_value"));
    my_map.insert("m1", my_map2);
    my_map.insert("m2", std::move(my_map2));
    mylist1.push_back(Dynamic_String("list ele1"));
    mylist1.push_back(Dynamic_String("list ele2"));
    mylist2 = mylist1;
    mylist2.push_back(Dynamic_Int(1000));
    mylist2.push_back(Dynamic_Double(3.14));
    my_map.insert("mylist", mylist1);
    my_map.insert("mylist3", mylist1);
    my_map.insert("mylist2", mylist2);
    mylist3 = std::move(mylist1);
    my_map.insert("empty", mylist1);
    my_map.insert("ori-list1", mylist3);

    my_map.erase("mylist");

    cout << my_map.str() << endl;
}

void test_map() {
    //Dynamic_Map my_map;

    //Dynamic_Map *inner_map = new Dynamic_Map();
    //inner_map->insert("inner_key",new Dynamic_String("inner_value"));

    //my_map.insert("my_key", inner_map);
    //Generic_Value *p = &my_map;
    //cout << p->str() << endl;
}

void test_list() {
    //Dynamic_Map my_map;

    //Dynamic_List *inner_lst = new Dynamic_List();
    //inner_lst->push_back(Dynamic_String("string_val"));

    //Dynamic_List *lst_in_lst = new Dynamic_List();
    //lst_in_lst->push_back(Dynamic_String("string_val1"));
    //lst_in_lst->push_back(Dynamic_String("string_val2"));
    //inner_lst->push_back(lst_in_lst);

    //Dynamic_Map *map_in_lst = new Dynamic_Map();
    //map_in_lst->insert("key", new Dynamic_String("string_in_map"));
    //inner_lst->push_back(map_in_lst);

    //my_map.insert("my_key", inner_lst);
    //Generic_Value *p = &my_map;
    //cout << p->str() << endl;
}

std::string test() {
    std::string myString("yniiq");
    //return std::move(myString);
    return myString;
}

#include <vector>
int main() {
    std::vector<int> v = { 1, 2, 3, 4 };
    //std::cout << test() << std::endl;
    test_string();
    //test_list();
    //test_map();
 
//    Dynamic_List l;
 //   l.push_back(Dynamic_String("string_val1"));

    return 0;
}

