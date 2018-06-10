#include <gtest/gtest.h>
#include "../Dynamic_String.h"
#include "../Dynamic_List.h"
#include "../Dynamic_Base_Type.h"
#include "../Dynamic_Object_Builder.h"
#include "../Dynamic_Map.h"

TEST(StringTest, nomral) {
    ASSERT_STREQ(Dynamic_String("abcºº").str().c_str(), "\"abcºº\"");
    ASSERT_STREQ(Dynamic_Int(100).str().c_str(), "100");
    ASSERT_STREQ(Dynamic_Int(0x7FFFFFFF).str().c_str(), "2147483647");

    Dynamic_Double d(1 / 3.0f);
    Dynamic_Float f(1 / 3.0f);
    double d_raw = atof(d.str().c_str());
    float f_raw = (float)atof(f.str().c_str());
    ASSERT_TRUE(d_raw > 0.333f && d_raw < 0.3334f);
    ASSERT_TRUE(f_raw > 0.333f && f_raw < 0.3334f);

    Dynamic_List lst;
    Dynamic_List sub_list;
    Dynamic_Map m;
    m.insert("key1", Dynamic_Int(101));
    sub_list.push_back(Dynamic_Int(1));
    sub_list.push_back(Dynamic_Int(2));
    lst.push_back(Dynamic_Int(100));
    lst.push_back(Dynamic_String("abcºº"));
    lst.push_back(Dynamic_Double(3.1));
    lst.push_back(sub_list);
    lst.push_back(m);
    ASSERT_STREQ(lst.str().c_str(), "[100,\"abcºº\",3.1,[1,2],{\"key1\":101}]");

    Dynamic_Map m1;
    m1.insert("key1", Dynamic_Int(101));
    m1.insert("key2", Dynamic_Double(3.1));
    m1.insert("key3", lst);
    m1.insert("key4", m);
    ASSERT_STREQ(m1.str().c_str(), R"({"key1":101,"key2":3.1,"key3":[100,"abcºº",3.1,[1,2],{"key1":101}],"key4":{"key1":101}})");
}

TEST(StringTest, empty) {
    ASSERT_STREQ(Dynamic_String().str().c_str(), "\"\"");
    ASSERT_STREQ(Dynamic_Int().str().c_str(), "0");
    ASSERT_STREQ(Dynamic_List().str().c_str(), "[]");
    ASSERT_STREQ(Dynamic_Map().str().c_str(), "{}");
}

TEST(StringTest, oneElement) {
    Dynamic_List lst;
    lst.push_back(Dynamic_Int(1));
    ASSERT_STREQ(lst.str().c_str(), "[1]");

    Dynamic_Map m;
    m.insert("k", Dynamic_String("v"));
    ASSERT_STREQ(m.str().c_str(), R"({"k":"v"})");
}

TEST(opTest, baseType) {
    Dynamic_Int i(100);
    i.set(102);
    ASSERT_EQ(i.get(), 102);

    Dynamic_Double d(1/3.0f);
    d.set(1/6.0f);
    ASSERT_DOUBLE_EQ(d.get(), 1/6.0f);

    Dynamic_String s("abc");
    s.set("def");
    ASSERT_STREQ(s.get().c_str(), "def");

}

TEST(opTest, list) {
    Dynamic_List l;
    l.push_back(Dynamic_Int(102));
    ASSERT_EQ(dynamic_cast<Dynamic_Int *>(&l.back())->get(), 102);

    l.push_back(Dynamic_String("aaa"));
    ASSERT_STREQ(dynamic_cast<Dynamic_String *>(&l.back())->get().c_str(), "aaa");

    Dynamic_List sub_list;
    sub_list.push_back(Dynamic_Int(1001));
    sub_list.push_back(Dynamic_Int(1002));
    l.push_back(sub_list);
    sub_list.push_back(Dynamic_Int(1003));  
    ASSERT_EQ(dynamic_cast<Dynamic_List *>(&l.back())->size(), 2);
    ASSERT_STREQ(l.str().c_str(), R"([102,"aaa",[1001,1002]])");

    ASSERT_EQ(l.size(), 3);
    l.pop_back();
    l.pop_back();
    ASSERT_EQ(l.size(), 1);

    Dynamic_List l2(l); //copy from l
    ASSERT_NE(&l.back(), &l2.back());

    ASSERT_EQ(dynamic_cast<Dynamic_Int *>(&l2.back())->get(), 102);
    l2.push_back(Dynamic_Int(103));
    l2.push_back(Dynamic_Int(104));

    ASSERT_EQ(l.size(), 1);
    ASSERT_EQ(l2.size(), 3);
    ASSERT_STREQ(l.str().c_str(), R"([102])");
    ASSERT_STREQ(l2.str().c_str(), R"([102,103,104])");

    l.pop_back();

    EXPECT_THROW(l.pop_back(), std::runtime_error);
    EXPECT_THROW(l.back(), std::runtime_error);


    size_t pre_size = l2.size();
    Generic_Value* pre = &l2.back();
    Dynamic_List l3(std::move(l2));
    Generic_Value* now = &l3.back();
    ASSERT_EQ(pre, now);
    ASSERT_EQ(l2.size(), 0);
    ASSERT_EQ(l3.size(), pre_size);

}

TEST(opTest, map) {
    Dynamic_Map m;
    m.insert("k1", Dynamic_Int(102));
    m.insert("k2", Dynamic_Int(103));
    m.insert("k3", Dynamic_Int(104));
    m.insert("k4", Dynamic_String("s2"));
    ASSERT_EQ(dynamic_cast<Dynamic_Int *>(&m.get("k1"))->get(), 102);
    ASSERT_EQ(m.size(), 4);

    Dynamic_Map m2(m);
    ASSERT_NE(&m.get("k1"), &m2.get("k1"));

    m.erase("k2");
    ASSERT_EQ(m.size(), 3);
    ASSERT_EQ(m2.size(), 4);

    EXPECT_THROW(m.get("k2"), std::runtime_error);
    EXPECT_THROW(m.erase("k2"), std::runtime_error);
    EXPECT_THROW(m.get("k500"), std::runtime_error);
    EXPECT_THROW(m.erase("k500"), std::runtime_error);

    m.insert("k30", Dynamic_Int(105));
    m2.insert("k300", Dynamic_Int(1005));

    ASSERT_EQ(dynamic_cast<Dynamic_Int *>(&m.get("k30"))->get(), 105);
    EXPECT_THROW(m.get("k300"), std::runtime_error);

    ASSERT_EQ(dynamic_cast<Dynamic_Int *>(&m2.get("k300"))->get(), 1005);
    EXPECT_THROW(m2.get("k30"), std::runtime_error);

    size_t pre_size = m.size();
    Generic_Value* pre = &m.get("k1");
    Dynamic_Map m3(std::move(m));
    Generic_Value* now = &m3.get("k1");
    ASSERT_EQ(pre, now);
    ASSERT_EQ(m.size(), 0);
    ASSERT_EQ(m3.size(), pre_size);
}

TEST(build, normal) {
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

    auto src_string = my_map.str();
    Dynamic_Object_Builder object_builder;
    std::unique_ptr<Generic_Value> new_map(object_builder.build(src_string));
    std::unique_ptr<Generic_Value> clone_map(new_map->clone());

    ASSERT_STREQ(my_map.str().c_str(), new_map->str().c_str());
    ASSERT_STREQ(clone_map->str().c_str(), new_map->str().c_str());
}

TEST(build, thread_safe) {
    //....
}
