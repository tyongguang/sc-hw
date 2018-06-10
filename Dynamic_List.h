#ifndef _DYNAMIC_LIST_H_
#define _DYNAMIC_LIST_H_

#include <mutex>
#include <list>
#include "Generic_Value.h"

class Dynamic_List : public Generic_Value {
public:
    Dynamic_List();
    Dynamic_List(const Dynamic_List& lst);
    Dynamic_List(Dynamic_List&& lst);
    Dynamic_List& operator = (const Dynamic_List& src);
    Dynamic_List& operator = (Dynamic_List&& src);
    ~Dynamic_List();
    Generic_Value& push_back(const Generic_Value& val);
    Generic_Value& push_back(Generic_Value&& val);
    void pop_back();
    Generic_Value& back();

    virtual std::string str() override;
    virtual Generic_Value* clone() const override;
    virtual Generic_Value* move_clone() override;
private:
    std::mutex mutex_;
    std::list<Generic_Value *> lst_;
};

#endif /* _DYNAMIC_LIST_H_ */