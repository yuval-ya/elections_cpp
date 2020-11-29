#pragma once
#include "String.h"
#include <ostream>
using namespace std;

class Person
{
private:
    String  _name;
    int     _id;
    int     _birth_year;
    int     _district_num;
    bool    _is_voted;
    bool    _is_candidate;
public:
    Person(const String&, int idnum, int year, int district_num);
    Person(const Person& p);
    ~Person();
    
    const String& getName() const { return _name; }
    int getID() const { return _id; };
    int getYear() const { return _birth_year; };
    int getDistrict() const { return _district_num; }
    bool isVoted() const { return _is_voted; }
    bool isCandidate() const { return _is_candidate; }
    

    friend ostream& operator<<(ostream& os, const Person& p);
};

