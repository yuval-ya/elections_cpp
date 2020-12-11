#pragma once
#include "String.h"
#include "CandidatesArray.h"
#include "District.h"

class Party
{
	// A class representing a Party in the elections

private:
	const int			_id;
	String				_name;
    PersonPtr		    _first_candidate;
	int					_total_candidates = 0,
						_total_votes = 0;
	CandidatesArray		_candidates;
	
public:
	static int total_parties;

	Party(const String& name, PersonPtr candidate);
	Party(const Party& p);
	~Party();

	int get_id() const { return _id; }
	const String& get_name() const { return _name; }
	int get_total_candidates() const { return _total_candidates; }
	int get_total_votes() const { return _total_votes; }
	const PersonList& get_candidates_list_from_district(int district_id) const { return _candidates[district_id - 1]; }
	const CandidatesArray& get_candidates_array() const { return _candidates; }
    const Person& get_candidate() const { return *_first_candidate; }

	void set_total_candidates(int val) { _total_candidates = val; }
    void set_first_candidate(PersonPtr candidate) { _first_candidate = candidate; }

	// add a new candidate to the candidate list according to the district id
	void add_candidate(PersonPtr p, int district_id);

	// add a new empty list to Candidates Array
	void add_district_to_candidates_arr();

	// add value to the total number of candidates the party get in the elections 
	void add_total_candidates(int val) { _total_candidates += val; }
	void add_total_votes(int val) { _total_votes += val; }

	friend std::ostream& operator<<(std::ostream& os, const Party& p);
};


