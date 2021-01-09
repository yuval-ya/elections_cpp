#include "ElectionsRoundLoader.h"
#include "DistrictLoader.h"

using namespace mySTL;
using namespace std;

namespace elections
{

	void ElectionsRoundLoader::loadDistricts(istream& in, Elections& elections) {
		int numOfDistricts;
		in.read(rcastc(&numOfDistricts), sizeof(numOfDistricts));
		checkFile(in);

		for (int i = 0; i < numOfDistricts; i++) {
			elections.getDistricts().push_back(DistrictLoader::load(in));
		}
	}
	void ElectionsRoundLoader::loadVoters(istream& in, Elections& elections) {
		int numOfPerson;
		in.read(rcastc(&numOfPerson), sizeof(numOfPerson));
		checkFile(in);

		for (int i = 0; i < numOfPerson; i++) {
			int districtID = 0, vote = 0, candidate = 0;

			PersonPtr person = new Person(in, districtID, vote, candidate);
			District& district = elections.findDistrict(districtID);
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

			PersonPtr firstCandidate = elections.findPerson(firstCandidateID);
			elections.getParties().push_back(party);
			party->setFirstCandidate(firstCandidate);
			firstCandidate->setAsCandidate(party);

			for (auto district : elections.getDistricts())
				district->getPartiesData().push_back(make_tuple(party,0,0));

			loadCandidatesArray(in, elections, party);
		}
	}

	void ElectionsRoundLoader::loadCandidatesArray(istream& in, Elections& elections, Party* party) {
		Elections::DistrictArray& districts = elections.getDistricts();

		int sizeOfCandidatesArray = 0, districtID = 0, sizeOfCandidatesList = 0, candidateID = 0;
		in.read(rcastc(&sizeOfCandidatesArray), sizeof(sizeOfCandidatesArray));
		checkFile(in);

		for (int j = 0; j < sizeOfCandidatesArray; j++)
		{
			in.read(rcastc(&districtID), sizeof(districtID));
			in.read(rcastc(&sizeOfCandidatesList), sizeof(sizeOfCandidatesList));
			checkFile(in);
			party->getCandidatesArray().push_back(make_tuple(&elections.findDistrict(districtID), Elections::PersonList()));
			Elections::PersonList& candidatesList = party->getCandidateList(districtID);

			for (int k = 0; k < sizeOfCandidatesList; k++)
			{
				in.read(rcastc(&candidateID), sizeof(candidateID));
				checkFile(in);
				PersonPtr candidate = elections.findPerson(candidateID);
				candidatesList.push_back(candidate);
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

	void ElectionsRoundLoader::saveDistricts(std::ostream& out, const Elections::DistrictArray& districts) {
		int size = districts.size();
		out.write(rcastcc(&size), sizeof(size));
		for (auto district : districts)
			DistrictLoader::save(out, district);
	}

	template<class T>
	static void saveStruct(std::ostream& out, const T& pointersStruct) {

	}

	void ElectionsRoundLoader::saveVotes(ostream& out,const Elections::VotesList& votesList) {
		int size = votesList.size();
		out.write(rcastcc(&size), sizeof(size));
		for (auto vote : votesList) {
			int personID = get<0>(vote)->getID();
			int partyID = get<1>(vote)->getId();
			out.write(rcastcc(&personID), sizeof(personID));
			out.write(rcastcc(&partyID), sizeof(partyID));
			if (!out.good()) throw;
			/*
			*
			*
			*/
		}
	}
}
