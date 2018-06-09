#ifndef _DYNAMIC_STRING_H_
#define _DYNAMIC_STRING_H_

#include "Dynamic_BaseType.h"
#include <mutex>

class Dynamic_String : public Dynamic_BaseType<std::string> {
public:
    Dynamic_String() {}
    Dynamic_String(const char * s);

    virtual std::string str() override;
    virtual Generic_Value* clone() const override;
    virtual Generic_Value * move_clone() override;
};

#endif /* _DYNAMIC_STRING_H_ */