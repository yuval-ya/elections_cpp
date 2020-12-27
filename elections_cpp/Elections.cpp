#include <iostream>
#include <typeinfo>
#include "Elections.h"
#include "ElectionsRoundLoader.h"

namespace elections {

Elections::Elections(const Date& date): _date(date)
{
}
Elections::Elections(std::istream& in){
	load(in);
}

Elections::~Elections() {
	_districts.makeEmpty();
	_parties.makeEmpty();
}




bool Elections::addDistrict(const String& name, int number_of_candidates, DistrictType type)
{
    District* newDistrict;
    
    if (number_of_candidates < 0)
        return false;

    switch (type) {
        case DistrictType::DIVIDED:
				newDistrict = new DividedDistrict(name, number_of_candidates);
			break;
        case DistrictType::UNIFIED:
				newDistrict = new UnifiedDistrict(name, number_of_candidates);
            break;
        default:
				return false;
            break;
    }

	_districts.add(newDistrict);
    for (int i = 0; i < _parties.getLength(); i++){
        newDistrict->getPartiesData().add(&_parties[i]);
    }
    
    _parties.addDistrictToParty(newDistrict);
    return true;
}

bool Elections::addPerson(const String& name, int id, int birth_year, int distric_id)
{
    if (_voters.getPersonPtr(id) != nullptr || distric_id > _districts.getLength() || distric_id <= 0) {
        return false;
    }
    District& district = _districts.get(distric_id);
	PersonPtr newPerson = new Person(name, id, birth_year, &district);
	_voters.addPerson(newPerson);
    district.getVoters().addPerson(newPerson);
    return true;
}


bool Elections::addParty(const String& name, int candidate_id)
{
    PersonPtr candidate = _voters.getPersonPtr(candidate_id);
    if (candidate == nullptr || candidate->isCandidate()) {
        return false;
    }
    Party* newParty = new Party(name, candidate);
    _parties.add(newParty);
    _districts.addPartyToDistrict(newParty);
    candidate->setAsCandidate(newParty);

	for (int i = 0; i < _districts.getLength(); i++) {
		newParty->getCandidatesArray().add(&_districts[i]);
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
	_votes.addVote(person, &party);
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




bool Elections::load(std::istream& in) {
	_date.load(in);
	ElectionsRoundLoader::loadDistricts(in, *this);
	ElectionsRoundLoader::loadVoters(in, *this);
	ElectionsRoundLoader::loadParties(in, *this);
	ElectionsRoundLoader::loadVotes(in, *this);
	return true;
}

bool Elections::save(std::ostream& out) const {
	_date.save(out);
	_districts.save(out);
	_voters.save(out);
	_parties.save(out);
	_votes.save(out);
	return true;
}

}

