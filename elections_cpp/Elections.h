#pragma once
#include "PersonList.h"
#include "PartyArray.h"
#include "DistrictArray.h"
class Elections
{
private:
    int				_day,	
					_month, 
					_year;
    PersonList		_voters;
    DistrictArray	_districs;
    PartyArray		_parties;
public:
    Elections(int day = 1, int month = 1, int year = 2021);
    
    void add_distric(String name, int number_of_candidates);
    bool add_person(String name, int id, int birth_year, int distric_num);
    void add_party(String name, int candidate_id);
    bool add_person_as_candidate(int person_id, int party_id, int district_id);
	bool vote(int person_id, int party_id);
	void finish_election();

    void print_voters() const;
    void print_districts() const;
    void print_parties() const;

	friend class District;
};


