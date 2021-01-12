#include "Test.h"
#include <iostream>

using namespace std;
using namespace elections;

void Test::test(Elections& election)
{
	election.addDistrict("A", 5, DistrictType::UNIFIED);
	election.addDistrict("B", 10, DistrictType::DIVIDED);

	election.addPerson("yuval", "000000001", 1996, 1);
	election.addPerson("oded", "000000011", 1996, 2);

	election.addParty("LIKUD", "000000001");
	election.addParty("AVODA", "000000011");

	election.addDistrict("C", 3, DistrictType::UNIFIED);

	/*election.addPerson("yuval", 1, 1996, 1);*/
	election.addPerson("tamir", "000000002", 1994, 1);
	election.addPerson("ohad", "000000003", 1996, 1);
	election.addPerson("nir", "000000004", 1994, 1);
	election.addPerson("gali", "000000005", 1996, 1);
	election.addPerson("gil", "000000006", 1994, 1);
	election.addPerson("itay", "000000007", 1996, 1);
	election.addPerson("omer", "000000008", 1997, 1);
	election.addPerson("hadar", "000000009", 1998, 1);
	election.addPerson("adi", "000000010", 1992, 1);
	/*election.addPerson("oded", 11, 1996, 2);*/
	election.addPerson("gal", "000000012", 1996, 2);
	election.addPerson("shaked", "000000013", 1996, 2);
	election.addPerson("mali", "000000014", 1996, 2);
	election.addPerson("zohar", "000000015", 1996, 2);
	election.addPerson("yuval", "000000016", 1996, 2);
	election.addPerson("tamir", "000000017", 1994, 2);
	election.addPerson("ohad", "000000018", 1996, 2);
	election.addPerson("nir", "000000019", 1994, 2);
	election.addPerson("gali", "000000020", 1996, 2);
	election.addPerson("gil", "000000021", 1994, 3);
	election.addPerson("itay", "000000022", 1996, 3);
	election.addPerson("omer", "000000023", 1997, 3);
	election.addPerson("hadar", "000000024", 1998, 3);
	election.addPerson("adi", "000000025", 1992, 3);
	election.addPerson("oded", "000000026", 1996, 3);
	election.addPerson("gal", "000000027", 1996, 3);
	election.addPerson("shaked", "000000028", 1996, 3);
	election.addPerson("mali", "000000029", 1996, 3);
	election.addPerson("zohar", "000000030", 1996, 3);

	//election.addParty("LIKUD", 1);
	//election.addParty("AVODA", 11);
	election.addParty("LIBRMAN", "000000021");

	election.addPersonAsCandidate("000000002", 1, 1);
	election.addPersonAsCandidate("000000003", 1, 1);
	election.addPersonAsCandidate("000000004", 1, 1);
	election.addPersonAsCandidate("000000005", 2, 1);
	election.addPersonAsCandidate("000000006", 2, 1);
	election.addPersonAsCandidate("000000007", 2, 1);
	election.addPersonAsCandidate("000000008", 3, 1);
	election.addPersonAsCandidate("000000009", 3, 1);
	election.addPersonAsCandidate("000000010", 3, 1);
	election.addPersonAsCandidate("000000012", 1, 2);
	election.addPersonAsCandidate("000000013", 1, 2);
	election.addPersonAsCandidate("000000014", 1, 2);
	election.addPersonAsCandidate("000000015", 2, 2);
	election.addPersonAsCandidate("000000016", 2, 2);
	election.addPersonAsCandidate("000000017", 2, 2);
	election.addPersonAsCandidate("000000018", 3, 2);
	election.addPersonAsCandidate("000000019", 3, 2);
	election.addPersonAsCandidate("000000020", 3, 2);
	election.addPersonAsCandidate("000000022", 1, 3);
	election.addPersonAsCandidate("000000023", 1, 3);
	election.addPersonAsCandidate("000000024", 1, 3);
	election.addPersonAsCandidate("000000025", 2, 3);
	election.addPersonAsCandidate("000000026", 2, 3);
	election.addPersonAsCandidate("000000027", 2, 3);
	election.addPersonAsCandidate("000000028", 3, 3);
	election.addPersonAsCandidate("000000029", 3, 3);
	election.addPersonAsCandidate("000000030", 3, 3);

	election.vote("000000001", 2);
	election.vote("000000002", 2);
	election.vote("000000003", 3);
	election.vote("000000004", 1);
	election.vote("000000005", 2);
	election.vote("000000006", 3);
	election.vote("000000007", 2);
	election.vote("000000008", 2);
	election.vote("000000009", 2);
	election.vote("000000010", 1);
	election.vote("000000011", 2);
	election.vote("000000012", 3);
	election.vote("000000013", 2);
	election.vote("000000014", 2);
	election.vote("000000015", 3);
	election.vote("000000016", 3);
	election.vote("000000017", 2);
	election.vote("000000018", 3);
	election.vote("000000019", 2);
	election.vote("000000020", 2);
	election.vote("000000021", 3);
	election.vote("000000022", 3);
	election.vote("000000023", 2);
	election.vote("000000024", 2);
	election.vote("000000025", 1);
	election.vote("000000026", 2);
	election.vote("000000027", 3);
	election.vote("000000028", 1);
	election.vote("000000029", 2);
	election.vote("000000030", 1);

}


