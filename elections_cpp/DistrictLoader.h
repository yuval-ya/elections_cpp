#pragma once

#include "DividedDistrict.h"
#include "UnifiedDistrict.h"
namespace elections {

	class DistrictLoader
	{
	public:
		static District* load(std::istream& in);
		static bool save(std::ostream& out ,District* district);
	};

}