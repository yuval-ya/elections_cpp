#pragma once
#include <iostream>
#include "ElectionsRoundLoader.h"

namespace elections {


class ElectionsLoader
{
	// A class to load and save elections according to the type of the election (deal with polymorphism)

public:
	static Elections* load(std::istream& in);
	static bool save(std::ostream& out, Elections* elections);
};

}