#pragma once
#include <iostream>
#include "District.h"

namespace elections {

class CandidatesArray;

class CandidatesArrayLoader {

public:
    static void save(std::ostream& out,const CandidatesArray& arr);
    static void load(std::istream& in, CandidatesArray& arr);

};   

}
