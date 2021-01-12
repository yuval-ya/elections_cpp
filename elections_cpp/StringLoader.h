#pragma once
#include <string>
#include <fstream>
#include "File_Handler.h"

class StringLoader
{
public:
	static std::string load(std::istream& in);
	static void save(std::ostream& out, const std::string& str);
};

