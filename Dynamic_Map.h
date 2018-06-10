#ifndef _DYNAMIC_MAP_H_
#define _DYNAMIC_MAP_H_

#include "Generic_Value.h"
#include <mutex>
#include <map>

class Dynamic_Map : public Generic_Value {
public:
    Dynamic_Map();    
    ~Dynamic_Map();
    Dynamic_Map(const Dynamic_Map& m);
    Dynamic_Map(Dynamic_Map&& m);
    Generic_Value& insert(const std::string& key, const Generic_Value& val);
    Generic_Value& insert(const std::string& key, Generic_Value&& val);
    void erase(const std::string& key);
    Generic_Value& get(const std::string& key);
    size_t size();

    virtual std::string str() override;
    virtual Generic_Value* clone() const override;
    virtual Generic_Value* move_clone() override;
private:
    std::map<std::string, Generic_Value *> m_;
    std::mutex mutex_;
};

#endif /* _DYNAMIC_MAP_H_ */