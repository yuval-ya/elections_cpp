//
//  UnifiedDistrict.cpp
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 16/12/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#include "UnifiedDistrict.h"

namespace elections {

UnifiedDistrict::UnifiedDistrict(String name, int numberOfCandidates) : District(name, numberOfCandidates) {}

UnifiedDistrict::UnifiedDistrict(const UnifiedDistrict& other) : District(other), _winnerCandidate(other._winnerCandidate) {}

const DynamicArray& UnifiedDistrict::evalPartition(){
    District::evalPartition();
    
    //
    
     return _candidatePartition;
}






}

