#include "ElectionsRoundLoader.h"
#include "DistrictLoader.h"

using namespace mySTL;
using namespace std;

namespace elections
    {
    
    void ElectionsRoundLoader::loadDistricts(istream& in, Elections& elections) {
        int numOfDistricts;
        in.read(rcastc(&numOfDistricts), sizeof(numOfDistricts));
        
        for (int i = 0; i < numOfDistricts; i++) {
            elections.getDistricts().push_back(DistrictLoader::load(in));
        }
    }
    
    void ElectionsRoundLoader::loadVoters(istream& in, Elections& elections) {
        int numOfPerson;
        in.read(rcastc(&numOfPerson), sizeof(numOfPerson));
        
        for (int i = 0; i < numOfPerson; i++) {
            int districtID = 0, vote = 0, candidate = 0;
            
            PersonPtr person = new Person(in, districtID, vote, candidate); // PersonPtr deletes itself
            District& district = elections.findDistrict(districtID);
            person->setDistrict(&district);
            
            elections.getVoters().push_back(person);
            district.getVoters().push_back(person);
        }
    }
    
    void ElectionsRoundLoader::loadParties(istream& in, Elections& elections) {
        int numOfParties;
        in.read(rcastc(&numOfParties), sizeof(numOfParties));
        
        for (int i = 0; i < numOfParties; i++) {
            int firstCandidateID = 0;
            Party* party = new Party(in, firstCandidateID);
            
            try {
                PersonPtr firstCandidate = elections.findPerson(firstCandidateID);
                firstCandidate->setAsCandidate(party);
                party->setFirstCandidate(firstCandidate);
                elections.getParties().push_back(party);
                
                for (auto district : elections.getDistricts())
                    district->getPartiesData().push_back(make_tuple(party,0,0));
                
                loadCandidatesArray(in, elections, party);
            }
            catch (...) {
                delete party;
                throw;
            }
        }
    }
    
    void ElectionsRoundLoader::loadCandidatesArray(istream& in, Elections& elections, Party* party) {
        int sizeOfCandidatesArray = 0, districtID = 0, sizeOfCandidatesList = 0, candidateID = 0;
        in.read(rcastc(&sizeOfCandidatesArray), sizeof(sizeOfCandidatesArray));
        
        for (int j = 0; j < sizeOfCandidatesArray; j++)
        {
            in.read(rcastc(&districtID), sizeof(districtID));
            in.read(rcastc(&sizeOfCandidatesList), sizeof(sizeOfCandidatesList));
            party->getCandidatesArray().push_back(make_tuple(&elections.findDistrict(districtID), Elections::PersonList()));
            Elections::PersonList& candidatesList = party->getCandidateList(districtID);
            
            for (int k = 0; k < sizeOfCandidatesList; k++)
            {
                in.read(rcastc(&candidateID), sizeof(candidateID));
                PersonPtr candidate = elections.findPerson(candidateID);
                candidate->setAsCandidate(party);
                candidatesList.push_back(candidate);
            }
        }
    }
    
    
    void ElectionsRoundLoader::loadVotes(istream& in, Elections& elections) {
        int numOfVotes;
        in.read(rcastc(&numOfVotes), sizeof(numOfVotes));
        for (int i = 0; i < numOfVotes; i++)
        {
            int personID = 0, partyID = 0;
            in.read(rcastc(&personID), sizeof(personID));
            in.read(rcastc(&partyID), sizeof(partyID));
            elections.vote(personID, partyID);
        }
    }
    
    
    void ElectionsRoundLoader::saveDistricts(std::ostream& out, const Elections::DistrictArray& districts) {
        int size = districts.size();
        out.write(rcastcc(&size), sizeof(size));
        for (auto district : districts)
            DistrictLoader::save(out, district);
    }
    
    
    void ElectionsRoundLoader::saveVotes(ostream& out,const Elections::VotesList& votesList) {
        int size = votesList.size();
        out.write(rcastcc(&size), sizeof(size));
        for (auto vote : votesList) {
            int personID = get<0>(vote)->getID();
            int partyID = get<1>(vote)->getId();
            out.write(rcastcc(&personID), sizeof(personID));
            out.write(rcastcc(&partyID), sizeof(partyID));
        }
    }
    }
