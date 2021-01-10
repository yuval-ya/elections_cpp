#include "Party.h"
#include "District.h"
#include "StringLoader.h"

using namespace std;

namespace elections {

int Party::totalParties = 0;

Party::Party(const string& name, PersonPtr candidate) :
	_id(++totalParties), _name(name), _firstCandidate(candidate), _totalCandidates(0), _totalVotes(0)
{
}

Party::Party(const Party& other) :
	_id(other._id), _name(other._name), _firstCandidate(other._firstCandidate),
	_totalCandidates(other._totalCandidates) , _totalVotes(other._totalVotes),
	_candidates(other._candidates)
{
}

Party::Party(istream& in, int& firstCandidateID) : _firstCandidate(nullptr) {
	totalParties++;
	load(in, firstCandidateID);
}

Party::~Party() {
	
}

void Party::setName(const string& name)
{
	_name = name;
}

void Party::setId(int id) {
	_id = id;
}

void Party::setTotalCandidates(int val) {
	_totalCandidates = val;
}

void Party::setFirstCandidate(PersonPtr candidate) {
	_firstCandidate = candidate;
}

Party::PersonList& Party::getCandidateList(int district_id) {

	auto iter = find_if(_candidates.begin(), _candidates.end(),
		[district_id](DistrictTuple tp)->bool { return get<0>(tp)->getId() == district_id; });
	
	if (iter == _candidates.end())
		throw invalid_argument("Invalid district ID");
    
	return get<1>(*iter);
}
const Party::PersonList& Party::getCandidateList(int district_id) const {
	
	auto iter = find_if(_candidates.begin(), _candidates.end(),
		[district_id](DistrictTuple tp)->bool { return get<0>(tp)->getId() == district_id; });

    if (iter == _candidates.end())
        throw invalid_argument("Invalid district ID");

	return get<1>(*iter);
}

void Party::load(istream& in, int& firstCandidateID) {

	in.read(rcastc(&_id), sizeof(_id));
	_name = StringLoader::load(in);
	in.read(rcastc(&firstCandidateID), sizeof(firstCandidateID));
	in.read(rcastc(&_totalCandidates), sizeof(_totalCandidates));
}

void Party::save(ostream& out) const {
	int firstCandidateID = _firstCandidate->getID();

	out.write(rcastcc(&_id), sizeof(_id));
	StringLoader::save(out, _name);
	out.write(rcastcc(&firstCandidateID), sizeof(firstCandidateID));
	out.write(rcastcc(&_totalCandidates), sizeof(_totalCandidates));

	saveCandidatesArray(out);
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
	} 	 
}

ostream& operator<<(ostream& os, const Party& p) {
	os << "Party ID: " << p._id << " | Name: " << p._name << " | First candidate ID: " << p._firstCandidate->getID();
	return os;
}

}
