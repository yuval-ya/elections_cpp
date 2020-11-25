#pragma once
#include "String.h"

class Person
{
private:
    const String _name;
    const int _id;
    const int _birth_year;
    const int _district_num;
    bool _voted;
public:
    Person(const String&, int idnum, int year, int district_num);
    ~Person();
    
    const String& get_name() const { return _name; }
    int get_id() const { return _id; };
    int get_year() const { return _birth_year; };
    int get_district() const { return _district_num; }
    bool voted() const { return _voted; }

};

