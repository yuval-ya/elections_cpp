#include "Person.h"
#include <iostream>

Person::Person(const String& name, int idnum, int year, int district_num) :
_name(name), _id(idnum), _birth_year(year), _district_num(district_num), _is_voted(false), _is_candidate(false)
{
}

Person::Person(const Person& p) :
_name(p._name), _id(p._id), _birth_year(p._birth_year), _district_num(p._district_num), _is_voted(p._is_voted), _is_candidate(p._is_candidate)
{
}

Person::~Person(){
}


ostream& operator<<(ostream& os, const Person& p) {
    os << "Person Name: " << p.getName() << " | ID: " << p.getID() << " | District: " << p.getDistrict();
    return os;
}
