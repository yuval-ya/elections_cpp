#include <iostream>
#include "Elections.h"

using namespace std;

int main(void) {
    
    Elections election;
    
//    election.add_distric("NY", 2);
//    election.add_distric("NJ", 3);
//    election.add_distric("TT", 1);
//    election.add_party("paapa", 123);


    election.add_party("paapa", 123);
    election.add_party("paapa", 123);
    election.add_party("paapa", 123);
    election.add_distric("NV", 3);
    election.add_distric("NV", 3);

//    election.add_party("Kahol Lavan", 2222);
//    election.add_distric("CA", 1);
//    election.add_party("Meretz", 3333);
    return 0;
}

