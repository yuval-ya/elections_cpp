#pragma once
#include <cstring>
#include <iostream>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

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

	bool load(std::istream& in);
	bool save(std::ostream& out) const;

	String& operator=(const String&);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
};
