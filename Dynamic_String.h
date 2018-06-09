#ifndef _DYNAMIC_STRING_H_
#define _DYNAMIC_STRING_H_

#include "Generic_Value.h"
#include <mutex>

class Dynamic_String : public Generic_Value {
public:
    Dynamic_String();
    
    Dynamic_String(std::string _s);

    ~Dynamic_String();
	
	virtual void set(const std::string& val);
	
	virtual std::string get_str();

    virtual std::string to_string();
private:
    std::string s;
    std::mutex str_mutex;
};

#endif /* _DYNAMIC_STRING_H_ */