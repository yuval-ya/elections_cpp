#include "String.h"
using namespace std;
String::String() : _str(nullptr), _len(0) {
}

String::String(const char* str) : _str(nullptr)
{
	set(str);
}

String::String(const String& str) {
	const char* tmp = str.get();
	_len = strlen(tmp);
	_str = new char[_len + 1];
    
	for (int i = 0; i < _len; i++) {
		_str[i] = tmp[i];
	}
	_str[_len] = '\0';
}

String::~String()
{
	delete[] _str;
}

bool String::set(const char *str) {
	if (_str)
		delete[] _str;

	_len = strlen(str);
	_str = new char[_len + 1];

	for (int i = 0; i < _len; i++) {
		_str[i] = str[i];
	}
	_str[_len] = '\0';
    return true;
}

String& String::operator=(const String& other){
    if (this != &other) {
        if (_str)
            delete[] _str;
        
        _len = other._len;
        _str = new char[_len + 1];
        
        memcpy(_str, other._str, _len);
        _str[_len] = '\0';
    }
    return *this;
}

ostream& operator<<(ostream& os, const String& str) {
	os << str._str;
	return os;
}


bool String::load(istream& in) {
	if (_str)
		delete[] _str;

	in.read(rcastc(&_len), sizeof(_len));
	_str = new char[_len + 1];
	in.read(rcastc(_str), sizeof(char)*_len);
	_str[_len] = '\0';

	return true;
}

bool String::save(ostream& out) const {
	out.write(rcastcc(&_len), sizeof(_len));
	out.write(rcastcc(_str), sizeof(char)*_len);
	return true;
}