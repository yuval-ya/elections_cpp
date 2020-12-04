//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <iostream>
#include "Elections.h"
#include "Menu.h"

using namespace std;

int main(void) {
	//_CrtDumpMemoryLeaks();
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//int* arr = new int[100];
    

	Elections election;
	Menu menu(election);
	menu.start();


//    Elections election;
//
//	election.add_distric("A", 4);
//    election.add_distric("B", 4);
//	election.add_distric("C", 4);
//
//	election.add_party("LIKUD", 1234);
//	election.add_party("AVODA", 5678);
//	election.add_party("DA LIBRMAN", 1358);
//
//    election.add_person("yuval", 1, 1996, 1);
//	election.add_person("tamir", 2, 1994, 1);
//	election.add_person("ohad", 3, 1996, 1);
//	election.add_person("nir", 4, 1994, 1);
//	election.add_person("gali", 5, 1996, 2);
//	election.add_person("gil", 6, 1994, 2);
//	election.add_person("itay", 7, 1996, 2);
//	election.add_person("omer", 8, 1997, 2);
//	election.add_person("hadar", 9, 1998, 3);
//	election.add_person("adi", 10, 1992, 3);
//    election.add_person("oded", 11, 1996, 3);
//	election.add_person("gal", 12, 1996, 3);
//	election.add_person("shaked", 13, 1996, 3);
//	election.add_person("mali", 14, 1996, 1);
//	election.add_person("zohar", 15, 1996, 2);
//
//	election.add_person_as_candidate(1, 1, 1);
//    election.add_person_as_candidate(2, 1, 1);
//	election.add_person_as_candidate(3, 3, 1);
//	election.add_person_as_candidate(4, 2, 1);
//	election.add_person_as_candidate(5, 1, 2);
//	election.add_person_as_candidate(6, 2, 2);
//	election.add_person_as_candidate(7, 1, 2);
//	election.add_person_as_candidate(8, 3, 2);
//
//	election.vote(1, 1);
//	election.vote(2, 1);
//	election.vote(3, 1);
//	election.vote(4, 1);
//	election.vote(5, 1);
//	election.vote(6, 1);
//	election.vote(7, 1);
//	election.vote(8, 1);
//	election.vote(9, 1);
//	election.vote(10, 2);
//	election.vote(11, 2);
//	election.vote(12, 2);
//	election.vote(13, 2);
//	election.vote(14, 2);
//	election.vote(15, 2);
//	election.vote(1, 2);
//
//	cout << "--------------------------------------- " << endl;
//	election.print_districts();
//	cout << "--------------------------------------- " << endl;
//	election.print_parties();
//	cout << "--------------------------------------- " << endl;
//	election.print_voters();
//	cout << "--------------------------------------- " << endl;
//
//	election.finish_election();

    
    return 0;
}

