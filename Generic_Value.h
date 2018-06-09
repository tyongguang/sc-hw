#ifndef _GENERIC_VALUE_H_
#define _GENERIC_VALUE_H_
#include <string>
#include <memory>

class Generic_Value {
public:
    Generic_Value() {
    }
    virtual ~Generic_Value() {
    };
    virtual std::string str() {
        return "";
    }

    virtual std::string getType() {
        return "";
    }
    virtual Generic_Value* clone() const {
        return  NULL;
    }
    virtual Generic_Value * move_clone() {
        return  NULL;
    }
    //virtual Generic_Value& operator = (const Generic_Value& v) = 0;
    //virtual Generic_Value& operator = (Generic_Value&& v) = 0;
};



#endif /* _GENERIC_VALUE_H_ */