#pragma once

#include "Elections.h"
namespace elections {
	class Menu
	{
	private:
		static const int MAX_SIZE = 100;

		static bool options(Elections&, int choice);
		static bool newDistrict(Elections&);
		static bool newParty(Elections&);
		static bool newCitizen(Elections&);
		static bool setCitizenAsCandidate(Elections&);
		static bool vote(Elections&);
		static void printStatistics(Elections&);
		static void printResults(Elections&);
		static void finish(Elections&);
	public:
		static void start(Elections&);
		static void test(Elections&);
	};

}
