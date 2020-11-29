#include <iostream>
#include "Elections.h"

using namespace std;

int main(void) {
    
    Elections election;
//    election.add_distric("NY", 2);
//    election.add_distric("NJ", 3);
//    election.add_distric("TT", 1);
//    election.add_party("paapa", 123);

    election.add_distric("NY", 3);
    election.add_distric("CA", 3);
    election.add_party("A", 123);
    election.add_party("B", 123);
    election.add_party("C", 123);
    election.add_party("D", 123);

    election.add_distric("NV", 3);
    election.add_distric("NV", 3);

    election.add_person("yuval", 1, 1996, 1);
    election.add_person_as_candidate(1, 1, 1);
    election.add_person("oded", 2, 1996, 1);
    election.add_person_as_candidate(2, 1, 1);
    return 0;
}

