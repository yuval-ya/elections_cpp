#pragma once
#include "String.h"
#include "PersonList.h"

class District
{
private:
	const int	_id;
	String		_name;
	int			_number_of_candidates;
	int			_number_of_voters = 0;
	int			_number_of_citizens = 0;
	PersonList	_voters;
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

	PersonPtr addPerson(const Person& p);
	const Person& addPerson(PersonPtr p);

	PersonPtr getPersonPtr(int idnum);
	const Person& getPerson(int idnum) const;

	friend ostream& operator<<(ostream& os, const District& d);
};

