#include "Party.h"
using namespace std;

namespace elections {

int Party::totalParties = 0;

Party::Party(const String& name, PersonPtr candidate) :
	_id(++totalParties), _name(name), _firstCandidate(candidate)
{
}

Party::Party(const Party& p) :
	_id(p._id), _name(p._name), _firstCandidate(p._firstCandidate),
	_totalCandidates(p._totalCandidates) , _totalVotes(p._totalVotes),
	_candidates(District::totalDistricts) 
{
}

Party::~Party() {
	
}

bool Party::setTotalCandidates(int val)
{
    _totalCandidates = val;
    return true;
}

bool Party::setFirstCandidate(PersonPtr candidate)
{
    _firstCandidate = candidate;
    return true;
}

void Party::addCandidate(PersonPtr p, int district_id) {
	_candidates.get(district_id).addPerson(p);
}


ostream& operator<<(ostream& os, const Party& p) {
	os << "Party ID: " << p._id << " | Name: " << p._name << " | First candidate ID: " << p._firstCandidate->getID();
	return os;
}

void Party::addDistrictToCandidatesArr()
{
	_candidates.add();
}

}
