#pragma once
#include "String.h"
#include "CandidatesArray.h"
#include "District.h"

class Party
{
private:
	const int			_id;
	String				_name;
	int					_first_candidate_id,
						_total_candidates = 0,
						_total_votes = 0;
	CandidatesArray		_candidates;
	
public:
	static int total_parties;

	Party(const String& name, int candidate_id);
	Party(const Party& p);
	~Party();

	int get_id() const { return _id; }
	int get_candidate_id() const { return _first_candidate_id; }
	const String& get_name() const { return _name; }
	int get_total_candidates() const { return _total_candidates; }
	int get_total_votes() const { return _total_votes; }

	void set_candidate_id(int candidate_id) { _first_candidate_id = candidate_id; }

	void add_candidate(PersonPtr p, int district_id);
	void add_district_to_candidates_arr();
	void add_total_candidates(int val) { _total_candidates += val; }
	void add_total_votes(int val) { _total_votes += val; }

	void print_final_candidates_for_district(int district_id, int size) const;
	void print_election_result() const;

	friend ostream& operator<<(ostream& os, const Party& p);
};


