//
//  UnifiedDistrict.h
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 16/12/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#pragma once
#include "District.h"

namespace elections {

class UnifiedDistrict : public District {
    
private:
    PersonPtr _winnerCandidate;
public:
    UnifiedDistrict(String name, int numberOfCandidates);
    ~UnifiedDistrict();
    UnifiedDistrict(const UnifiedDistrict&);
    
    
    const Person& getWinnerCandidate() const { return *_winnerCandidate; }
    
    virtual const DynamicArray& evalPartition();

    
    bool setWinnerCandidate(PersonPtr p) { _winnerCandidate = p; return true; }
};


}
