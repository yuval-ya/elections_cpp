#include "Elections.h"


Elections::Elections(int day, int month, int year) : _day(day), _month(month), _year(year) {}

void Elections::add_distric(String name, int number_of_candidates)
{
    District new_distric(name, number_of_candidates);
    _districs.add(new_distric);
    _partys.add_district_to_party();
}

bool Elections::add_person(String name, int id, int birth_year, int distric_num)
{
    // check if person can vote 
    if (!(_voters.getPersonPtr(id) == nullptr) || distric_num > District::total_districts) {
        return false;
    }
    Person new_person(name, id, birth_year, distric_num);
    PersonPtr person_ptr = _voters.addPerson(new_person);
    _districs.get(distric_num).addPerson(person_ptr);
    return true;
}

void Elections::add_party(String name, int candidate_id)
{
    Party new_party = Party(name,candidate_id);
    _partys.add(new_party);
}

bool Elections::add_person_as_candidate(int person_id, int party_id, int district_id)
{
    if (district_id <= District::total_districts)
    {
        PersonPtr candidate = _districs.get(district_id).getPersonPtr(person_id);
        
        if (!(candidate == nullptr) && !candidate->isCandidate())
        {
            _partys.get(party_id).add_candidate(candidate, district_id);
            candidate->setAsCandidate();
            return true;
        }
    }
    return false;
}

void Elections::print_voters() const
{
    _voters.printList();
}

void Elections::print_district() const
{
    _districs.print();
}

void Elections::print_partys() const
{
    _partys.print();
}
