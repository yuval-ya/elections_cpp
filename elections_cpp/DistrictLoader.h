#pragma once

#include "DividedDistrict.h"
#include "UnifiedDistrict.h"
namespace elections {

	class DistrictLoader
	{
		// A class to load and save districts according to its type(deal with polymorphism)

	public:
		static District* load(std::istream& in);
		static bool save(std::ostream& out ,District* district);
	};

}