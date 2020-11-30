#include "District.h"

int District::total_districts = 0;


District::District(String name, int number_of_candidates) : 
	_id(++total_districts), _name(name), _number_of_candidates(number_of_candidates)
{
}

District::District(const District& d) :
	_id(d._id), _name(d._name), _number_of_candidates(d._number_of_candidates),
	_votes_by_parties(Party::total_parties)
{
	_number_of_voters = d.get_number_of_voters();
}

District::~District() {
	// ...
}

float District::calc_voters_percentage() const
{ 
	return _number_of_voters / static_cast<float>(get_citizens_number()) * 100; 
}

float District::calc_party_percent_in_votes(int party_id) const
{
	return (_votes_by_parties[party_id - 1] / static_cast<float>(_number_of_voters)) * 100;
}

int District::calc_final_sum_of_candidates_from_party(int party_id) const {
	int res = static_cast<int>((_votes_by_parties[party_id - 1] / static_cast<float>(_number_of_voters)) * _number_of_candidates);
	return res;
}

PersonPtr District::addPerson(const Person& p) {
	return _voters.addPerson(p);
}
const Person& District::addPerson(PersonPtr p) {
	return _voters.addPerson(p);
}

PersonPtr District::getPersonPtr(int idnum) {
	return _voters.getPersonPtr(idnum);
}
const Person& District::getPerson(int idnum) const {
	return _voters.getPerson(idnum);
}

ostream& operator<<(ostream& os, const District& d) {
	os << d._id << " | " << d._name << " | " << d._number_of_candidates << " | ";
	return os;
}

bool District::vote(int party_id) {
	_votes_by_parties[party_id - 1]++;
	_number_of_voters++;
	return true;
}

void District::add_party_to_votes_arr()
{
	_votes_by_parties.add();
}

int District::get_winner_party_id() const {
	return _votes_by_parties.get_max_votes() + 1;
}
