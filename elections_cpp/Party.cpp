#include "Party.h"
#include "District.h"
#include "StringLoader.h"

using namespace std;

namespace elections {

int Party::totalParties = 0;

Party::Party(const string& name, PersonPtr candidate) :
	_id(++totalParties), _name(name), _firstCandidate(candidate), _totalCandidates(0), _totalVotes(0),
	_candidates(District::totalDistricts)
{
}

Party::Party(const Party& p) :
	_id(p._id), _name(p._name), _firstCandidate(p._firstCandidate),
	_totalCandidates(p._totalCandidates) , _totalVotes(p._totalVotes),
	_candidates(District::totalDistricts) 
{
}

Party::Party(istream& in, int& firstCandidateID) : _firstCandidate(nullptr) {
	totalParties++;
	load(in, firstCandidateID);
}

Party::~Party() {
	
}

bool Party::setName(const string& name)
{
	_name = name;
	return true;
}

bool Party::setId(int id) {
	_id = id;
	return true;
}

bool Party::setTotalCandidates(int val) {
	_totalCandidates = val;
	return true;
}

bool Party::setFirstCandidate(PersonPtr candidate) {
	_firstCandidate = candidate;
	return true;
}

Party::PersonList& Party::getCandidateList(int district_id) {
	auto iter = find_if(_candidates.begin(), _candidates.end(),
		[district_id](DistrictTuple tp)->bool { return get<0>(tp)->getId() == district_id; });
	
	if (iter == _candidates.end())
		throw;
	/*
	*
	*
	*
	*/

	return get<1>(*iter);
}
const Party::PersonList& Party::getCandidateList(int district_id) const {
	auto iter = find_if(_candidates.begin(), _candidates.end(),
		[district_id](DistrictTuple tp)->bool { return get<0>(tp)->getId() == district_id; });

	if (iter == _candidates.end())
		throw;
	/*
	*
	*
	*
	*/

	return get<1>(*iter);
}

bool Party::load(istream& in, int& firstCandidateID) {

	in.read(rcastc(&_id), sizeof(_id));
	_name = StringLoader::load(in);
	in.read(rcastc(&firstCandidateID), sizeof(firstCandidateID));
	in.read(rcastc(&_totalCandidates), sizeof(_totalCandidates));
	if (!in.good()) {
		std::cout << "Error reading" << std::endl;
		exit(-1);
	}
	return true;
}

bool Party::save(ostream& out) const {
	int firstCandidateID = _firstCandidate->getID();

	out.write(rcastcc(&_id), sizeof(_id));
	StringLoader::save(out, _name);
	out.write(rcastcc(&firstCandidateID), sizeof(firstCandidateID));
	out.write(rcastcc(&_totalCandidates), sizeof(_totalCandidates));
	if (!out.good()) {
		std::cout << "Error writing" << std::endl;
		exit(-1);
	}
	
	saveCandidatesArray(out);
	return true;
}

void Party::saveCandidatesArray(std::ostream& out) const {
	int candidatesSize = _candidates.size();
	out.write(rcastcc(&candidatesSize), sizeof(candidatesSize));	

	for (auto districtTuple : _candidates) {
		int districtID = get<0>(districtTuple)->getId();
		out.write(rcastcc(&districtID), sizeof(districtID));

		int lstSize = get<1>(districtTuple).size();
		out.write(rcastcc(&lstSize), sizeof(lstSize));

		for (auto personPtr : get<1>(districtTuple)) {
			int personID = personPtr->getID();
			out.write(rcastcc(&personID), sizeof(personID));
		}

		if (!out.good()) {
			std::cout << "Error writing" << std::endl;
			exit(-1);
		}
	} 	 

}

ostream& operator<<(ostream& os, const Party& p) {
	os << "Party ID: " << p._id << " | Name: " << p._name << " | First candidate ID: " << p._firstCandidate->getID();
	return os;
}

}
