#include "District.h"

int District::total_districts = 0;


District::District(String name, int number_of_candidates) : 
	_id(0), _name(name), _number_of_candidates(number_of_candidates)
{
}

District::District(const District& d) :
	_id(++total_districts), _name(d._name), _number_of_candidates(d._number_of_candidates)
{
	_number_of_voters = d.get_voters();
	_number_of_citizens = d.get_citizens();
}

District::~District() {
	// ...
}

float District::get_voters_percentage() const
{ 
	return _number_of_voters / static_cast<float>(_number_of_citizens) * 100; 
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
	os << d._id << " | " << d._name << " | " << d._number_of_candidates;
	return os;
}