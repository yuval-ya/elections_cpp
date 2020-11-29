#include "Elections.h"


Elections::Elections(int day, int month, int year) : _day(day), _month(month), _year(year) {}

void Elections::add_distric(String name, int number_of_candidates)
{
    District new_distric = District(name, number_of_candidates);
    _districs.add(new_distric);
    
    // Add distric to every party 
}

void Elections::add_person(String name, int id, int birth_year, int distric_num)
{
    // check if the person can vote
    Person new_person = Person(name, id, birth_year, distric_num);
    PersonPtr person_ptr = _voters.addPerson(new_person);
//    _districs.get(distric_num).addPerson(person_ptr);
//    ADD PERSON TO DISTRIC
    
}

void Elections::add_party(String name, int candidate_id)
{
    Party new_party = Party(name,candidate_id);
    _partys.add(new_party);
}

void Elections::add_person_as_candidate(int person_id, int party_id, int district_id)
{
//    PersonPtr candidate = _districs.get(district_id).getPersonPtr(person_id);
//    _partys.get(party_id).add_candidate(candidate, district_id);
}

void Elections::print_voters() const
{
    _voters.printList();
}
