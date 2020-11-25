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
    
    

};

