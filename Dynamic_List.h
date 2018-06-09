#ifndef _DYNAMIC_LIST_H_
#define _DYNAMIC_LIST_H_

#include <mutex>
#include <vector>
#include "Generic_Value.h"

class Dynamic_List : public Generic_Value {
public:
    Dynamic_List();
    
    ~Dynamic_List();

    void push_back(Generic_Value *val);
    
    void pop_back();

    Generic_Value *back();

    virtual std::string to_string();

private:
    std::mutex lst_mutex;
    std::vector<Generic_Value *> lst;
};

#endif /* _DYNAMIC_LIST_H_ */