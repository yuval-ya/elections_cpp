#pragma once

#include "Elections.h"

class Menu
{
private:
    static const int MAX_SIZE = 100;
    Elections& _election;
    
	bool options(int choice);
    bool new_district();
    bool new_party();
    bool new_citizen();
    bool set_citizen_as_candidate();
    bool vote();
	void print_statistics();
	void print_results();
	void finish();
public:
	Menu(Elections& e);
	Menu(const Menu&) = delete;
	~Menu();

    void start();
    
    
};

