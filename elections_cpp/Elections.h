#pragma once
#include "PersonList.h"
#include "PartyArray.h"
#include "DistrictArray.h"
class Elections
{
private:
    int _day, _month, _year;
    PersonList _voters;
    DistrictArray _districs;
    PartyArray _partys;
public:
    Elections(int day = 0, int month = 0, int year = 0);
    
    void add_distric(String name, int number_of_candidates);
    bool add_person(String name, int id, int birth_year, int distric_num);
    void add_party(String name, int candidate_id);
    void add_person_as_candidate(int person_id, int party_id, int district_id);
    void print_voters() const;
};


