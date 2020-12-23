//
//  UnifiedDistrict.h
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 16/12/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#pragma once
#include <iostream>
#include "District.h"


namespace elections {

class UnifiedDistrict : public District {
    
private:
public:
    UnifiedDistrict(String name, int numberOfCandidates);
    UnifiedDistrict(const UnifiedDistrict&);
	UnifiedDistrict(std::istream& in);
    virtual ~UnifiedDistrict();

    virtual void evalPartition();
    
	virtual void type(std::ostream& os) const { os << "Unified"; }
    
    virtual std::ostream& showWinners(std::ostream&) const;

};


}
