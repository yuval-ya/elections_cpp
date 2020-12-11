#include "Party.h"
using namespace std;

int Party::total_parties = 0;

Party::Party(const String& name, PersonPtr candidate) :
	_id(++total_parties), _name(name), _first_candidate(candidate)
{
}

Party::Party(const Party& p) :
	_id(p._id), _name(p._name), _first_candidate(p._first_candidate), 
	_total_candidates(p._total_candidates) , _total_votes(p._total_votes),
	_candidates(District::total_districts) 
{
}

Party::~Party() {
	
}

bool Party::set_total_candidates(int val)
{
    _total_candidates = val;
    return true;
}

bool Party::set_first_candidate(PersonPtr candidate)
{
    _first_candidate = candidate;
    return true;
}

void Party::add_candidate(PersonPtr p, int district_id) {
	_candidates.get(district_id).addPerson(p);
}


ostream& operator<<(ostream& os, const Party& p) {
	os << "Party ID: " << p._id << " | Name: " << p._name << " | First candidate ID: " << p._first_candidate->getID();
	return os;
}

void Party::add_district_to_candidates_arr()
{
	_candidates.add();
}
