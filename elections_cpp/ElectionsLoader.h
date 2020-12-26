#pragma once
#include "SimpleElections.h"
namespace elections {

class ElectionsLoader
{
public:
	static Elections* load(std::istream& in);
	static bool save(std::ostream& out, Elections* elections);
};

}