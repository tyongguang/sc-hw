#ifndef _GENERIC_VALUE_H_
#define _GENERIC_VALUE_H_
#include <string>

class Generic_Value {
public:
    Generic_Value() {}
    virtual ~Generic_Value() {};
    virtual std::string to_string() = 0;
private:

};

#endif /* _GENERIC_VALUE_H_ */