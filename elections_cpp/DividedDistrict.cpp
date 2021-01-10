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

DividedDistrict::DividedDistrict(const string& name, int numberOfCandidates) : District(name, numberOfCandidates) {
}

DividedDistrict::DividedDistrict(const DividedDistrict& other) : District(other) {
}

DividedDistrict::DividedDistrict(std::istream& in) : District(in) {
}

DividedDistrict::~DividedDistrict() {
}

void DividedDistrict::evalPartition(){
    District::evalPartition();
	for (auto partyData : _partiesData) {
		int num_candidates = get<2>(partyData);
		get<0>(partyData)->addTotalCandidates(num_candidates);
		_chosenCandidates.push_back(get<0>(partyData)->getCandidatePtr());
	}
}

ostream& DividedDistrict::showWinners(ostream& out) const{
   
    for(auto partyData : _partiesData) {
        if (get<2>(partyData) > 0) {
            out << "First candidate of Party No." << get<0>(partyData)->getId() << ": ";
            out << get<0>(partyData)->getCandidate() << " with " ;
            out << get<2>(partyData) << " candidates" <<endl;
        }
        else break;
    }
    return out;
}

}

