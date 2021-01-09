#pragma once
#include "Elections.h"

namespace elections {

	class SimpleElections : public Elections
	{
		// A class representing a simple elections round

	public:
		SimpleElections(int numOfCandidates, const Date& date);
		SimpleElections(const Elections&) = delete;
		SimpleElections(std::istream& in);
		virtual ~SimpleElections();

		const District& getDistrict() const { return *_districts[0]; }
		District& getDistrict() { return *_districts[0]; }

		virtual bool addDistrict(const std::string& name, int number_of_candidates, DistrictType type) override;

		// add a new person to the voters list and to the district he belongs
		virtual bool addPerson(const std::string& name, int id, int birth_year, int distric_id = 1) override;

		// Add a person as a candidate of a party in a given district
		virtual bool addPersonAsCandidate(int person_id, int party_id, int distric_id = 1) override;

	};
}
