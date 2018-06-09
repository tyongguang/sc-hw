#ifndef _DYNAMIC_MAP_H_
#define _DYNAMIC_MAP_H_

#include "Generic_Value.h"
#include <mutex>
#include <map>

class Dynamic_Map : public Generic_Value {
public:
    Dynamic_Map();    

    ~Dynamic_Map();

    void insert(const std::string& key, Generic_Value *val);

    void erase(const std::string& key);

    Generic_Value *get(const std::string& key);

    virtual std::string to_string();
    
private:
    std::map<std::string, Generic_Value *> m;
    std::mutex map_mutex;
};

#endif /* _DYNAMIC_MAP_H_ */