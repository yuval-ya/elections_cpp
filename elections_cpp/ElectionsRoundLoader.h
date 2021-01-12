#pragma once
#include <iostream>
#include "Elections.h"

namespace elections
{
	class ElectionsRoundLoader
	{
		// A class that manages Elections file loading
        
	public:
		static void loadDistricts(std::istream& in, Elections& elections);
		static void loadVoters(std::istream& in, Elections& elections);
		static void loadParties(std::istream& in, Elections& elections);
		static void loadCandidatesArray(std::istream& in, Elections& elections, Party* party);
		static void loadVotes(std::istream& in, Elections& elections);
		
		static void saveVotes(std::ostream& out, const Elections::VotesList& lst);
		static void saveDistricts(std::ostream& out, const Elections::DistrictArray& lst);

		template<class T>
		static void saveStruct(std::ostream& out, const T& pointersStruct) {
			int size = pointersStruct.size();
			out.write(rcastcc(&size), sizeof(size));
			if (!out.good()) throw File_Error("Unable to write to file");

			for (auto obj : pointersStruct) 
				obj->save(out);
		}
	};
}


