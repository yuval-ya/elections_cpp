//
//  UnifiedDistrict.cpp
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 16/12/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#include <ostream>
#include "UnifiedDistrict.h"
using namespace std;

namespace elections {

UnifiedDistrict::UnifiedDistrict(String name, int numberOfCandidates) : District(name, numberOfCandidates) {}

UnifiedDistrict::UnifiedDistrict(const UnifiedDistrict& other) : District(other), _winnerCandidate(other._winnerCandidate) {}

UnifiedDistrict::~UnifiedDistrict() {
}

const DynamicArray& UnifiedDistrict::evalPartition(){
    District::evalPartition();
    
    // get the max from _candidatePartition and put the candidate in PersonPtr _winnerCandidate
    
     return _candidatePartition;
}


}

