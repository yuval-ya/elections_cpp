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

Party::Party(istream& in, string& firstCandidateID) : _firstCandidate(nullptr) {
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

void Party::load(istream& in, string& firstCandidateID) {

	in.read(rcastc(&_id), sizeof(_id));
	_name = StringLoader::load(in);
    firstCandidateID = StringLoader::load(in);
    in.read(rcastc(&_totalCandidates), sizeof(_totalCandidates));
	if (!in.good()) throw File_Error("Unable to read from file");

}

void Party::save(ostream& out) const {
	out.write(rcastcc(&_id), sizeof(_id));
	StringLoader::save(out, _name);
    StringLoader::save(out, _firstCandidate->getID());
	out.write(rcastcc(&_totalCandidates), sizeof(_totalCandidates));
	if (!out.good()) throw File_Error("Unable to write to file");

	saveCandidatesArray(out);
}

void Party::saveCandidatesArray(std::ostream& out) const {
	int candidatesSize = _candidates.size();
	out.write(rcastcc(&candidatesSize), sizeof(candidatesSize));	
	if (!out.good()) throw File_Error("Unable to write to file");

	for (auto districtTuple : _candidates) {
		int districtID = get<0>(districtTuple)->getId();
		out.write(rcastcc(&districtID), sizeof(districtID));

		int lstSize = get<1>(districtTuple).size();
		out.write(rcastcc(&lstSize), sizeof(lstSize));
		if (!out.good()) throw File_Error("Unable to write to file");
		for (auto personPtr : get<1>(districtTuple))
			StringLoader::save(out, personPtr->getID());
		
	}
}

ostream& operator<<(ostream& os, const Party& p) {
	os << "Party ID: " << p._id << " | Name: " << p._name << " | First candidate ID: " << p._firstCandidate->getID();
	return os;
}

}
