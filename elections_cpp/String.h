#pragma once
#include <cstring>
#include <ostream>

class String
{
    
    // Class to store a string
    
private:
	char * _str;
    long int _len;
public:
	String(const char *str);
	String(const String&);
	~String();

	const char* get() const { return _str; }
    long int get_len() const { return _len; }
	bool set(const char *str);

    String& operator=(String&);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
};

