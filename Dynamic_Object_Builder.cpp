#include "Dynamic_Object_Builder.h"
#include <iostream>
#include <json/json.h>
#include "Dynamic_BaseType.h"
#include "Dynamic_String.h"
#include "Dynamic_List.h"
#include "Dynamic_Map.h"

Generic_Value* ParseJSONValue(const Json::Value& val) {
    if (val.isString()) {
        return new Dynamic_String(val.asString());
    }
    else if (val.isInt()) {
        return new Dynamic_Int(val.asInt());
    }
    else if (val.isDouble()) {
        return new Dynamic_Double(val.asDouble());
    }
    throw std::runtime_error("json type not support");
    return NULL;
}

void ParseJSONTree(Generic_Value* parent, const Json::Value& root) {
    if (root.isObject()) {
        Dynamic_Map * m = dynamic_cast<Dynamic_Map*>(parent);
        for (Json::Value::const_iterator itr = root.begin(); itr != root.end(); ++itr) {
            if (itr->isObject()) {
                auto& child = m->insert(itr.key().asCString(), Dynamic_Map());
                ParseJSONTree(&child, *itr);
            }
            else if (itr->isArray()) {
                auto& child = m->insert(itr.key().asCString(), Dynamic_List());
                ParseJSONTree(&child, *itr);
            } else {
                std::unique_ptr<Generic_Value> v(ParseJSONValue(*itr));
                m->insert(itr.key().asCString(), std::move(*v));
            }
        }
    }
    else if (root.isArray()) {
        Dynamic_List * lst = dynamic_cast<Dynamic_List*>(parent);
        for (Json::Value::const_iterator itr = root.begin(); itr != root.end(); ++itr) {
            if (itr->isObject()) {
                auto& child = lst->push_back(Dynamic_Map());
                ParseJSONTree(&child, *itr);
            } else if (itr->isArray()) {
                auto& child = lst->push_back(Dynamic_List());
                ParseJSONTree(&child, *itr);
            } else {
                std::unique_ptr<Generic_Value> v(ParseJSONValue(*itr));
                lst->push_back(std::move(*v));
            }
        }
    }
}

Generic_Value* Dynamic_Object_Builder::build(const std::string& json) {
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    std::string errors;
    if (reader->parse(json.c_str(), json.c_str() + json.size(), &root, &errors)){
        if (root.isObject()) {
            auto * result = new Dynamic_Map();
            ParseJSONTree(result, root);
            return result;
        }
        else if (root.isArray()) {
            auto result = new Dynamic_List();
            ParseJSONTree(result, root);
            return result;
        }
        throw std::runtime_error("json string invalid");
    }
    throw std::runtime_error(errors.c_str());
    return NULL;
}
