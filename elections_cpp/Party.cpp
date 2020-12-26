#include "Party.h"
#include "District.h"
using namespace std;

namespace elections {

int Party::totalParties = 0;

Party::Party(const String& name, PersonPtr candidate) :
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

bool Party::setName(const String& name)
{
	_name = name;
	return true;
}

bool Party::setId(int id) {
	_id = id;
	return true;
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

bool Party::load(istream& in, int& firstCandidateID) {

	in.read(rcastc(&_id), sizeof(_id));
	_name.load(in);
	in.read(rcastc(&firstCandidateID), sizeof(firstCandidateID));
	in.read(rcastc(&_totalCandidates), sizeof(_totalCandidates));

	return true;
}

bool Party::save(ostream& out) const {
	int firstCandidateID = _firstCandidate->getID();

	out.write(rcastcc(&_id), sizeof(_id));
	_name.save(out);
	out.write(rcastcc(&firstCandidateID), sizeof(firstCandidateID));
	out.write(rcastcc(&_totalCandidates), sizeof(_totalCandidates));
	_candidates.save(out);
	return true;
}

ostream& operator<<(ostream& os, const Party& p) {
	os << "Party ID: " << p._id << " | Name: " << p._name << " | First candidate ID: " << p._firstCandidate->getID();
	return os;
}

}
