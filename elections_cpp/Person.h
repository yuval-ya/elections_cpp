#pragma once
#include "String.h"

#include <ostream>
using namespace std;

class District;
class Party;

class Person
{
private:
    String				_name;
    int					_id;
    int					_birth_year;
    const District&		_district;
    const Party*		_vote;
	const Party*		_is_candidate;
public:
    Person(const String&, int id, int year,const District& district);
    Person(const Person& p);
    ~Person();
    
    const String& getName() const { return _name; }
    int getID() const { return _id; };
    int getYear() const { return _birth_year; };
	int getDistrictID() const;
	bool setAsCandidate(const Party* p);
	bool isCandidate() const;
	bool isVoted() const;
	bool setVote(const Party* p);

    friend ostream& operator<<(ostream& os, const Person& p);

};

