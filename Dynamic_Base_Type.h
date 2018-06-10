#ifndef _DYNAMIC_BASE_TYPE_H_
#define _DYNAMIC_BASE_TYPE_H_

#include "Generic_Value.h"
#include <stdint.h>
#include <mutex>
#include <sstream>

template<class T>
class Dynamic_Base_Type : public Generic_Value {
public:
    Dynamic_Base_Type()
        :value_(T()) {
    }

    Dynamic_Base_Type(const T& v) 
        : value_(v) {
    }

    ~Dynamic_Base_Type() {
    }

    virtual void set(const T& val) {
        value_ = val;
    }

    virtual const T& get() {
        return value_;
    }

    virtual std::string str() override {
        std::stringstream ss;
        ss << value_;
        return ss.str();
    }

    virtual Generic_Value* clone() const override {
        auto p = new Dynamic_Base_Type<T>();
        p->value_ = this->value_;
        return p;
    }

    virtual Generic_Value * move_clone() override {
        auto p = new Dynamic_Base_Type<T>();
        p->value_ = std::move(this->value_);
        return p;
    }
protected:
    T value_;
    std::mutex mutex_;
};

typedef Dynamic_Base_Type<int> Dynamic_Int;
typedef Dynamic_Base_Type<short> Dynamic_Short;
typedef Dynamic_Base_Type<double> Dynamic_Double;
typedef Dynamic_Base_Type<float> Dynamic_Float;

#endif /* _DYNAMIC_BASE_TYPE_H_ */