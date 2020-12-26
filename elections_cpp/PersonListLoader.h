#pragma once
#include <iostream>



namespace elections {

class DistrictArray;
class PersonList;

class PersonListLoader {

public:
    static void load(std::istream& in, PersonList& personList, DistrictArray& districtsArr);
 
};

}
