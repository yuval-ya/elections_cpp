#pragma once
#include <iostream>
#include <string>

class File_Error : public std::exception
{
private:
	std::string _msg;

public:
	File_Error() : _msg("File Error") {}
	File_Error(const char* msg) :_msg(msg) {}
	
	virtual const char* what() const throw()
	{
		return _msg.c_str();
	}
};

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>