#include "Party.h"

int Party::total_parties = 0;

Party::Party(const String& name, int candidate_id) : 
	_id(++total_parties), _name(name), _first_candidate_id(candidate_id)
{
    cout << "party ctor" <<endl;
}

Party::Party(const Party& p) :
	_id(p._id), _name(p._name), _first_candidate_id(p._first_candidate_id), 
	_total_candidates(p._total_candidates) , _total_votes(p._total_votes),
	_candidates(District::total_districts) 
{
    cout << "party copy ctor" <<endl;
}

Party::~Party() {
	
}

void Party::add_candidate(PersonPtr p, int district_id) {
	_candidates.get(district_id).addPerson(p);
}

ostream& operator<<(ostream& os, const Party& p) {
	os << "Party ID: " << p._id << " | Name: " << p._name << " | First candidate ID: " << p._first_candidate_id;
	return os;
}

void Party::add_district_to_candidates_arr()
{
	_candidates.add();
}
