#pragma once
#include "PersonList.h"
#include "PartyArray.h"
#include "DistrictArray.h"


class Elections
{
	// A class representing a Election round

private:
    int				_day,	
					_month, 
					_year;
    PersonList		_voters;
    DistrictArray	_districts;
    PartyArray		_parties;
public:
	Elections(int day = 1, int month = 1, int year = 2021);
	Elections(const Elections&) = delete;

    bool setDate(int year, int month, int day);

	const District& get_district(int district_id) const { return _districts[district_id - 1];  }
	const Party& get_party(int party_id) const { return _parties[party_id - 1]; }
	int get_num_districts() const { return _districts.get_length(); }
	int get_num_parties() const { return _parties.get_length(); }

	// add new district to the elections
    bool add_district(String name, int number_of_candidates);

	// add a new person to the voters list and to the district he belongs
    bool add_person(String name, int id, int birth_year, int distric_id);

	// add new party to the elections
    bool add_party(String name, int candidate_id);

	// Add a person as a candidate of a party in a given district
    bool add_person_as_candidate(int person_id, int party_id, int district_id);

	bool vote(int person_id, int party_id);

    void print_voters() const;
    void print_districts() const;
    void print_parties() const;
	
	// Performs a calculation of all votes in all districts and updates the number of 
	// votes and candidates each party received
	bool final_evaluation();

	// return a pointer tp Party array and it's size (as an output parameter) 
	// The array is sorted by the order of votes each party received (the winnig party in index 0) 
	Party** get_sorted_parties_arr(int& size);
};


