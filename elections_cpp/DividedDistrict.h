//
//  DividedDistrict.h
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 16/12/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#pragma once
#include <iostream>
#include "District.h"

namespace elections {

class DividedDistrict : public District {
    
private:
public:
    DividedDistrict(const String& name, int numberOfCandidates);
    DividedDistrict(const DividedDistrict&);
	DividedDistrict(std::istream& in);
    virtual ~DividedDistrict();
    
    virtual void evalPartition();
    
	virtual void type(std::ostream& os) const { os << "Divided" ;}

    virtual std::ostream& showWinners(std::ostream& os) const;

};


}
