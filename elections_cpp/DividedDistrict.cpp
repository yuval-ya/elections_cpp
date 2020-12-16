//
//  DividedDistrict.cpp
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 16/12/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#include "DividedDistrict.h"

namespace elections {

DividedDistrict::DividedDistrict(String name, int numberOfCandidates) : District(name, numberOfCandidates) {}

DividedDistrict::DividedDistrict(const DividedDistrict& other) : District(other) {}

const DynamicArray& DividedDistrict::evalPartition(){
    District::evalPartition();
    
    //
    
     return _candidatePartition;
}





}
