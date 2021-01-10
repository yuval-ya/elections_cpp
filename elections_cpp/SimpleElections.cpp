#include <iostream>
#include "SimpleElections.h"

using namespace std;

namespace elections {


	SimpleElections::SimpleElections(int numOfCandidates, const Date& date) : Elections(date)
	{
		District* dummy = new DividedDistrict("Dummy District", numOfCandidates);
		_districts.push_back(dummy);
	}

	SimpleElections::SimpleElections(std::istream& in) : Elections(in) {
	}

	SimpleElections::~SimpleElections() {
	}

	void SimpleElections::addDistrict(const string& name, int number_of_candidates, DistrictType type) {
	}

	void SimpleElections::addPerson(const string& name, int id, int birth_year, int distric_id) {
		Elections::addPerson(name, id, birth_year, 1);
	}

	void SimpleElections::addPersonAsCandidate(int person_id, int party_id, int distric_id) {
		Elections::addPersonAsCandidate(person_id, party_id, 1);
	}





}

