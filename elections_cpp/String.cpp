#include "String.h"

String::String(const char* str) : _str(nullptr)
{
	set(str);
}

String::String(const String& str) {
	const char* tmp = str.get();
	int size = strlen(tmp);
	_str = new char[size + 1];
    
	for (int i = 0; i < size; i++) {
		_str[i] = tmp[i];
	}
	_str[size] = '\0';
}

String::~String()
{
	delete _str;
}

void String::set(const char *str) {
	if (_str)
		delete[] _str;

	int size = strlen(str);
	_str = new char[size + 1];

	for (int i = 0; i < size; i++) {
		_str[i] = str[i];
	}
	_str[size] = '\0';
}


ostream& operator<<(ostream& os, const String& str) {
	os << str._str;
	return os;
}
