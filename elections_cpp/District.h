#pragma once
#include "String.h"
#include "PersonList.h"
#include "DynamicArray.h"
#include "Party.h"

class District
{
	// A class representing a District in the elections

private:
	const int		_id;
	String			_name;
	int				_number_of_candidates;
	int				_number_of_voters = 0,
					_winner_party = 0;
	PersonList		_voters;
	DynamicArray	_votes_by_parties;
	DynamicArray	_candidate_partition;
	
public:
	static int total_districts;

	District(String name, int number_of_candidates);
	District(const District&);
	~District();

	int get_id() const { return _id; }
	const String& get_name() const { return _name; }
	int get_number_of_candidates() const { return _number_of_candidates; }
	int get_number_of_voters() const { return _number_of_voters; }
    int get_citizens_number() const { return _voters.get_person_number(); }
	int get_party_votes(int party_id) const { return _votes_by_parties[party_id - 1]; }
	int get_party_candidates_num(int party_id) const { return _candidate_partition[party_id - 1]; }
	int get_winner_party() const { return _winner_party; }

	bool set_number_of_candidates(int number_of_candidates);

	// Calculation of the percentage of votes in the whole district
	float calc_voters_percentage() const;

	// Calculate the percentage of votes for a particular party out of the total number of votes
	float calc_party_percent_in_votes(int party_id) const;

	// Calculate the number of candidates for a particular party out of the total number of 
	// candidates in the district
	int calc_final_sum_of_candidates_from_party(int party_id) const;

	// Calculates the partition of candidates in the district according to the percentage of 
	// votes for each party
	int eval_partition();
	
	bool vote(int party_id);

	// Adds a new party for voting and calculation
	bool add_party_to_district();

	// add new person to voters list in the district
	PersonPtr addPerson(const Person& p);
	const Person& addPerson(PersonPtr p);

	// search and return person from voters list by id
	PersonPtr getPersonPtr(int idnum);
	const Person& getPerson(int idnum) const;

	friend std::ostream& operator<<(std::ostream& os, const District& d);
};

