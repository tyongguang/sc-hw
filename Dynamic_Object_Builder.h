#ifndef _DYNAMIC_OBJECT_BUILDER_H_
#define _DYNAMIC_OBJECT_BUILDER_H_

#include "Generic_Value.h"

class Dynamic_Object_Builder {
public:
    Generic_Value* build(const std::string& json);
};

#endif /* _DYNAMIC_TYPE_BUILDER_H_ */