//
//  UnifiedDistrict.cpp
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 16/12/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#include <iostream>
#include "UnifiedDistrict.h"
using namespace std;

namespace elections {

UnifiedDistrict::UnifiedDistrict(const String& name, int numberOfCandidates) : District(name, numberOfCandidates) {
}

UnifiedDistrict::UnifiedDistrict(const UnifiedDistrict& other) : District(other) {
}

UnifiedDistrict::UnifiedDistrict(istream& in) : District(in) {
}

UnifiedDistrict::~UnifiedDistrict() {
}

void UnifiedDistrict::evalPartition(){
    District::evalPartition(); // sort the array
    _partiesData[0].party->addTotalCandidates(_numberOfCandidates);  
	_chosenCandidates.addPerson(_partiesData[0].party->getCandidatePtr());
}

ostream& UnifiedDistrict::showWinners(ostream& out) const {
	out << "First candidate of Party No." << _partiesData[0].party->getId() << ": ";
	out << _partiesData[0].party->getCandidate() << " with " ;
    out << _numberOfCandidates << " candidates " <<endl;
    return out;
}

}

