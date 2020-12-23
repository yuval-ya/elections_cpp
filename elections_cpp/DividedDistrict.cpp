//
//  DividedDistrict.cpp
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 16/12/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#include <ostream>
#include "DividedDistrict.h"
using namespace std;

namespace elections {

DividedDistrict::DividedDistrict(String name, int numberOfCandidates) : District(name, numberOfCandidates) {
}

DividedDistrict::DividedDistrict(const DividedDistrict& other) : District(other) {
}

DividedDistrict::DividedDistrict(std::istream& in) : District(in) {
}

DividedDistrict::~DividedDistrict() {
}

void DividedDistrict::evalPartition(){
    District::evalPartition();
    
    for (int i = 0; i < _partiesData.getLength() ; i++){
        int num_candidates = _partiesData[i].candidates;
        _partiesData[i].party->addTotalCandidates(num_candidates);
		_chosenCandidates.addPerson(_partiesData[i].party->getCandidatePtr());
    }
}

ostream& DividedDistrict::showWinners(ostream& out) const{
    for(int i = 0; i < _partiesData.getLength() && _partiesData[i].candidates > 0; i++){
		out << "First candidate of Party No." << _partiesData[i].party->getId() << ": ";
		out << _partiesData[i].party->getCandidate() << " with " ;
        out << _partiesData[i].candidates << " candidates" <<endl;
    }
    return out;
}

}

