#pragma once

#include "Elections.h"

class Menu
{
private:
    static const int MAX_SIZE = 100;
   
	static bool options(Elections&,int choice);
	static bool new_district(Elections&);
	static bool new_party(Elections&);
	static bool new_citizen(Elections&);
	static bool set_citizen_as_candidate(Elections&);
	static bool vote(Elections&);
	static void print_statistics(Elections&);
	static void print_results(Elections&);
	static void finish(Elections&);
public:
	static void start(Elections&);
	static void test(Elections&);
};

