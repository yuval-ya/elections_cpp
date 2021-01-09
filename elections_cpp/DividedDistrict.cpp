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
	int size = _partiesData.size();
	for (int i = 0; i < size; i++) {
		int num_candidates = get<2>(_partiesData[i]);
		get<0>(_partiesData[i])->addTotalCandidates(num_candidates);
		_chosenCandidates.push_back(get<0>(_partiesData[i])->getCandidatePtr());
	}
}

ostream& DividedDistrict::showWinners(ostream& out) const{
	int size = _partiesData.size();
    for(int i = 0; i < size && get<2>(_partiesData[i]) > 0; i++){
		out << "First candidate of Party No." << get<0>(_partiesData[i])->getId() << ": ";
		out << get<0>(_partiesData[i])->getCandidate() << " with " ;
        out << get<2>(_partiesData[i]) << " candidates" <<endl;
    }
    return out;
}

}

