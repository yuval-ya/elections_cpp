#include <typeinfo>
#include "Elections.h"

namespace elections {

Elections::Elections(const Date& date): _date(date)
{
}

Elections::~Elections() {
}



bool Elections::addDistrict(String name, int number_of_candidates, DistrictType type)
{
    District* newDistrict;
    
    if (number_of_candidates < 0)
        return false;
    
    switch (type) {
        case DistrictType::DIVIDED:
            {
                DividedDistrict dDistrict(name, number_of_candidates);
                newDistrict = &_districts.add(dDistrict);
            }
            break;
        case DistrictType::UNIFIED:
            {
                UnifiedDistrict uDistrict(name, number_of_candidates);
                newDistrict = &_districts.add(uDistrict);
            }
            break;
            
        default:
            return false;
            break;
    }
 
    for (int i = 0; i < _parties.getLength(); i++){
        newDistrict->getPartiesData().add(&_parties[i]);
    }
    
    _parties.addDistrictToParty(newDistrict);
    return true;
}

bool Elections::addPerson(String name, int id, int birth_year, int distric_id)
{
    if (_voters.getPersonPtr(id) != nullptr || distric_id > _districts.getLength() || distric_id <= 0) {
        return false;
    }
    District& district = _districts.get(distric_id);
    Person new_person(name, id, birth_year, &district);
    PersonPtr person_ptr = _voters.addPerson(new_person);
    district.getVoters().addPerson(person_ptr);
    return true;
}

bool Elections::addParty(String name, int candidate_id)
{
    PersonPtr candidate = _voters.getPersonPtr(candidate_id);
    if (candidate == nullptr || candidate->isCandidate()) {
        return false;
    }
    Party new_party = Party(name, candidate);
    Party& p = _parties.add(new_party);
    _districts.addPartyToDistrict(&p);
    candidate->setAsCandidate(&p);

	for (int i = 0; i < _districts.getLength(); i++) {
		p.getCandidatesArray().add(&_districts[i]);
	}

    return true;
}

bool Elections::addPersonAsCandidate(int person_id, int party_id, int district_id)
{
    if (district_id <= _districts.getLength() && district_id > 0
        && party_id <= _parties.getLength() && party_id > 0)
    {
        PersonPtr candidate = _voters.getPersonPtr(person_id);
        
        if (candidate != nullptr && !candidate->isCandidate())
        {
            Party& party = _parties.get(party_id);
			party.getCandidatesArray().get(district_id).addPerson(candidate);
            candidate->setAsCandidate(&party);
            return true;
        }
    }
    return false;
}

bool Elections::vote(int person_id, int party_id)
{
    PersonPtr person = _voters.getPersonPtr(person_id);
    if (person == nullptr || person->isVoted() || party_id > _parties.getLength()) {
        return false;
    }

    int district_id = person->getDistrictID();
    _districts.get(district_id).vote(party_id);

	Party& party = _parties.get(party_id);
	party.addTotalVotes(1);
    return person->setVote(&party);
}


bool Elections::finalEvaluation() {
    int numOfDistricts = _districts.getLength();
    int numOfParties = _parties.getLength();
    
    for (int i = 0; i < numOfParties; i++)
        _parties[i].setTotalCandidates(0);
    
    for (int i = 0; i < numOfDistricts; i++)
        _districts[i].evalPartition();
    
    return true;
}


Party** Elections::getSortedPartiesArr(int& size) {
    int numOfParties = _parties.getLength();
    Party** res = new Party*[numOfParties];
    
    for (int i = 0; i < numOfParties; i++)
        res[i] = &_parties[i];

    PartyArray::mergeSort(res, 0, numOfParties - 1);
    size = numOfParties;
    return res;
}
}

