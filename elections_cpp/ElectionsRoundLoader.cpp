#include "ElectionsRoundLoader.h"

using namespace std;

namespace elections
{

	void ElectionsRoundLoader::loadDistricts(istream& in, Elections& elections) {
		int numOfDistricts;
		in.read(rcastc(&numOfDistricts), sizeof(numOfDistricts));
		checkFile(in);

		for (int i = 0; i < numOfDistricts; i++) {
			elections.getDistricts().add(DistrictLoader::load(in));
		}
	}
	void ElectionsRoundLoader::loadVoters(istream& in, Elections& elections) {
		int numOfPerson;
		in.read(rcastc(&numOfPerson), sizeof(numOfPerson));
		checkFile(in);

		for (int i = 0; i < numOfPerson; i++) {
			int districtID = 0, vote = 0, candidate = 0;

			PersonPtr person = new Person(in, districtID, vote, candidate);
			District& district = elections.getDistricts().get(districtID);
			person->setDistrict(&district);

			elections.getVoters().push_back(person);
			district.getVoters().push_back(person);
		}
	}

	void ElectionsRoundLoader::loadParties(istream& in, Elections& elections) {
		int numOfParties;
		in.read(rcastc(&numOfParties), sizeof(numOfParties));
		checkFile(in);

		for (int i = 0; i < numOfParties; i++) {
			int firstCandidateID = 0;
			Party* party = new Party(in, firstCandidateID);

			PersonPtr firstCandidate = *(std::find_if(elections.getVoters().begin(), elections.getVoters().end(),
				[firstCandidateID](PersonPtr p)->bool { return p->getID() == firstCandidateID; }));

			elections.getParties().add(party);
			party->setFirstCandidate(firstCandidate);
			firstCandidate->setAsCandidate(party);
			elections.getDistricts().addPartyToDistrict(party);
			loadCandidatesArray(in, elections, party);
		}
	}

	void ElectionsRoundLoader::loadCandidatesArray(istream& in, Elections& elections, Party* party) {
		DistrictArray& districts = elections.getDistricts();
		int sizeOfCandidatesArray = 0, districtID = 0, sizeOfCandidatesList = 0, candidateID = 0;
		in.read(rcastc(&sizeOfCandidatesArray), sizeof(sizeOfCandidatesArray));
		checkFile(in);

		for (int j = 0; j < sizeOfCandidatesArray; j++)
		{
			in.read(rcastc(&districtID), sizeof(districtID));
			in.read(rcastc(&sizeOfCandidatesList), sizeof(sizeOfCandidatesList));
			checkFile(in);
			party->getCandidatesArray().add(&districts.get(districtID));
			PersonList& candidatesList = party->getCandidatesArray().get(districtID);

			for (int k = 0; k < sizeOfCandidatesList; k++)
			{
				in.read(rcastc(&candidateID), sizeof(candidateID));
				checkFile(in);
				PersonPtr candidate = *(std::find_if(elections.getVoters().begin(), elections.getVoters().end(),
					[candidateID](PersonPtr p)->bool { return p->getID() == candidateID; }));
				candidatesList.addPerson(candidate);
				candidate->setAsCandidate(party);
			}
		}
	}


	void ElectionsRoundLoader::loadVotes(istream& in, Elections& elections) {
		int numOfVotes;
		in.read(rcastc(&numOfVotes), sizeof(numOfVotes));
		checkFile(in);
		for (int i = 0; i < numOfVotes; i++) {
			int personID = 0, partyID = 0;
			in.read(rcastc(&personID), sizeof(personID));
			in.read(rcastc(&partyID), sizeof(partyID));
			checkFile(in);
			elections.vote(personID, partyID);
		}
	}

	void ElectionsRoundLoader::checkFile(istream& in) {
		if (!in.good()) {
			std::cout << "Error reading" << std::endl;
			exit(-1);
		}
	}
}
