#pragma once
#include <iostream>
#include "Elections.h"

namespace elections
{
	class ElectionsRoundLoader
	{
	public:
		static void loadDistricts(std::istream& in, Elections& elections);
		static void loadVoters(std::istream& in, Elections& elections);
		static void loadParties(std::istream& in, Elections& elections);
		static void loadCandidatesArray(std::istream& in, Elections& elections, Party* party);
		static void loadVotes(std::istream& in, Elections& elections);
	};
}


