#pragma once
#include <cstring>
#include <ostream>
using namespace std;

class String
{
private:
	char * _str;
public:
	String(const char *str);
	String(const String&);
	~String();

	const char* get() const { return _str; }
	void set(const char *str); // delete if not needed
	friend ostream& operator<<(ostream& os, const String& str);
};

