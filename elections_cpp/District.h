#pragma once
#include "String.h"
#include "PersonList.h"
#include "DynamicArray.h"
#include "Party.h"

class District
{
private:
	const int		_id;
	String			_name;
	const int		_number_of_candidates;
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

	float calc_voters_percentage() const;
	float calc_party_percent_in_votes(int party_id) const;
	int calc_final_sum_of_candidates_from_party(int party_id) const;

	int eval_partition();
	
	bool vote(int party_id);
	void add_party_to_district();

	PersonPtr addPerson(const Person& p);
	const Person& addPerson(PersonPtr p);

	PersonPtr getPersonPtr(int idnum);
	const Person& getPerson(int idnum) const;

	friend ostream& operator<<(ostream& os, const District& d);
};

