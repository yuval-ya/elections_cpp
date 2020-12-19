#include <typeinfo>
#include "Elections.h"

namespace elections {

Elections::Elections() {
    setDate(1, 1, 1);
    
}

Elections::Elections(int day, int month, int year)
{
    setDate(year, month, day);
}


bool Elections::setDate(int year, int month, int day) {
    if (year < 1 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    _year = year;
    _month = month;
    _day = day;
    return true;
}

bool Elections::addDistrict(String name, int number_of_candidates, int type)
{
    District* newDistrict;
    
    if (type == 0){
        DividedDistrict dDistrict(name, number_of_candidates);
        newDistrict = &_districts.add(dDistrict);
    }
    else if (type == 1){
        UnifiedDistrict uDistrict(name, number_of_candidates);
        newDistrict = &_districts.add(uDistrict);
    }
    else
        return false;
    
    for (int i = 0; i < _parties.getLength(); i++){
        newDistrict->getPartiesData().add(&_parties[i]);
    }
    
    _parties.addDistrictToParty();
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
            party.addCandidate(candidate, district_id);
            candidate->setAsCandidate(&party);
            return true;
        }
    }
    return false;
}

void Elections::printVoters() const
{
    _voters.printList();
}

void Elections::printDistricts() const
{
    _districts.print();
}

void Elections::printParties() const
{
    _parties.print();
}

bool Elections::vote(int person_id, int party_id)
{
    PersonPtr person = _voters.getPersonPtr(person_id);
    if (person == nullptr || person->isVoted() || party_id > _parties.getLength()) {
        return false;
    }
    int district_id = person->getDistrictID();
    _districts.get(district_id).vote(party_id);
    _parties.get(party_id).addTotalVotes(1);
    return person->setVote(&(_parties.get(party_id)));
}


bool Elections::finalEvaluation() {
    int numOfDistricts = _districts.getLength();
    int numOfParties = _parties.getLength();
    
    for (int i = 0; i < numOfParties; i++)
    {
        _parties[i].setTotalCandidates(0);
    }
    
    for (int i = 0; i < numOfDistricts; i++)
    {
        District& district = _districts[i];
        district.evalPartition();
    }
    
    return true;
}



Party** Elections::getSortedPartiesArr(int& size) {
    int numOfParties = _parties.getLength();
    Party** res = new Party*[numOfParties];
    
    for (int i = 0; i < numOfParties; i++)
    {
        res[i] = &_parties[i];
    }
    PartyArray::mergeSort(res, 0, numOfParties - 1);
    size = numOfParties;
    return res;
}
}

