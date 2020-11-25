#pragma once
#include "String.h"

class District
{
private:
	const int	_id;
	String		_name;
	int			_number_of_candidates;
	int			_number_of_voters = 0;
	int			_number_of_citizens = 0;
	// list of person that can vote
	// result after the votes

public:
	static int total_districts;

	District(String name, int number_of_candidates);
	District(const District&);
	~District();

	int get_id() const { return _id; }
	const String& get_name() const { return _name; }
	int get_candidates() const { return _number_of_candidates; }
	int get_voters() const { return _number_of_voters; }
	int get_citizens() const { return _number_of_citizens; }
	float get_voters_percentage() const;
	
	void set_candidates(int candidates) { _number_of_candidates = candidates; }

};

