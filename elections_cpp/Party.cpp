#include "Party.h"

int Party::total_parties = 0;

Party::Party(const String& name, int candidate_id) : 
	_name(name), _first_candidate_id(candidate_id), _id(++total_parties),
	_candidates(District::total_districts)
{

}
Party::~Party() {
	
}

bool Party::add_candidate(PersonPtr p, int district_id) {
	_candidates.get(district_id).addPerson(p);
}

ostream& operator<<(ostream& os, const Party& p) {
	os << p._name << " | " << p._first_candidate_id;
	return os;
}

void Party::add_district_to_candidates_arr() {
	_candidates.add();
}