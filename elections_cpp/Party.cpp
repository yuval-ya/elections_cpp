#include "Party.h"

int Party::total_parties = 0;

Party::Party(const String& name, int candidate_id) : 
	_id(++total_parties), _name(name), _first_candidate_id(candidate_id)
{
    cout << "party ctor" <<endl;
}

Party::Party(const Party& p) :
	_id(p._id), _name(p._name), _first_candidate_id(p._first_candidate_id), 
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
	os << p._id << " | " << p._name << " | " << p._first_candidate_id << endl << p._candidates;
	return os;
}

void Party::add_district_to_candidates_arr()
{
	_candidates.add();
}

void Party::print_final_candidates_for_district(int district_id, int size) const
{
	_candidates[district_id - 1].printList(size);
}

