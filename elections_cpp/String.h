#pragma once
#include <cstring>
#include <ostream>

class String
{
    
    // Class to store a string
    
private:
	char * _str;
public:
	String(const char *str);
	String(const String&);
	~String();

	const char* get() const { return _str; }
	void set(const char *str);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
};

