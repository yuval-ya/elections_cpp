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
	String();
	String(const char *str);
	String(const String&);
	~String();

	const char* get() const { return _str; }
    long int getLen() const { return _len; }
	bool set(const char *str);

	int foo() { return 1; }

	String& operator=(const String&);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
};
