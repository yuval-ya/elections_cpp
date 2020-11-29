#pragma once
#include "String.h"
#include "CandidatesArray.h"
#include "District.h"

class Party
{
private:
	const int _id;
	String _name;
	int _first_candidate_id;
	CandidatesArray	_candidates;
	
public:
	static int total_parties;

	Party(const String& name, int candidate_id);

	~Party();

	int get_id() const { return _id; }
	int get_candidate_id() const { return _first_candidate_id; }
	const String& get_name() const { return _name; }

	void set_candidate_id(int candidate_id) { _first_candidate_id = candidate_id; }

	void add_candidate(PersonPtr p, int district_id);
	void add_district_to_candidates_arr();

	friend ostream& operator<<(ostream& os, const Party& p);
};


