#pragma once
#include "String.h"

class Party
{
private:
	const int _id;
	String _name;
	int _candidate_id;
	// add list of candidate for each district

public:
	static int total_parties;

	Party(const String& name, int candidate_id);
	~Party();

	int get_id() const { return _id; }
	int get_candidate_id() const { return _candidate_id; }
	const String& get_name() const { return _name; }

	void set_candidate_id(int candidate_id) { _candidate_id = candidate_id; }
};


