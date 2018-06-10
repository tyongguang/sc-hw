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
    virtual std::string str() = 0;
    virtual Generic_Value* clone() const = 0;
    virtual Generic_Value * move_clone() = 0;
};



#endif /* _GENERIC_VALUE_H_ */