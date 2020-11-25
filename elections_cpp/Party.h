#pragma once
#include "String.h"

class Party
{
private:
	const int _id;
	String _name;
	int _candidate_id;
	// list of candidate for each district

public:
	static int total_parties;
	Party(String& name, int candidate_id);
	~Party();
};

