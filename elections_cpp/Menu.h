#pragma once

#include "Elections.h"

class Menu
{
private:
    static const int MAX_SIZE = 100;
    Elections _election;
    
    bool new_district();
    bool new_party();
    bool new_citizen();
    bool set_citizen_as_candidate();
    bool vote();
    bool options(int choice);
public:
    void start();
    
    
};

