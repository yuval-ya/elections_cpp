#pragma once
#include <string>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class StringLoader
{
public:
	static std::string load(std::istream& in);
	static void save(std::ostream& out, const std::string& str);
};

