#pragma once
#include "PersonList.h"
#include "PartyArray.h"
#include "DistrictArray.h"

int compare_parties(const void* a, const void* b);

class Elections
{
private:
    int				_day,	
					_month, 
					_year;
    PersonList		_voters;
    DistrictArray	_districts;
    PartyArray		_parties;
public:
    Elections() {}
    Elections(int day, int month, int year);
	Elections(const Elections&) = delete;

    void setDate(int year, int month, int day);

	const District& get_district(int district_id) const { return _districts[district_id - 1];  }
	const Party& get_party(int party_id) const { return _parties[party_id - 1]; }
	int get_num_districts() const { return _districts.get_length(); }
	int get_num_parties() const { return _parties.get_length(); }

    bool add_distric(String name, int number_of_candidates);
    bool add_person(String name, int id, int birth_year, int distric_num);
    bool add_party(String name, int candidate_id);
    bool add_person_as_candidate(int person_id, int party_id, int district_id);
	bool vote(int person_id, int party_id);

    void print_voters() const;
    void print_districts() const;
    void print_parties() const;
	
	void final_evaluation();
	Party** get_sorted_parties_arr(int& size);
};


