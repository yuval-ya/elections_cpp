#include <iostream>
#include <typeinfo>
#include "Elections.h"
#include "ElectionsRoundLoader.h"

using namespace std;
using namespace mySTL;

namespace elections {

Elections::Elections(const Date& date): _date(date)
{
}
Elections::Elections(std::istream& in){
	load(in);
}

Elections::~Elections() {
	for (auto district : _districts)
		delete district;
	for (auto party : _parties)
		delete party;
}


bool Elections::addDistrict(const string& name, int number_of_candidates, DistrictType type)
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

	_districts.push_back(newDistrict);
	for (auto party : _parties) {
		newDistrict->getPartiesData().push_back(make_tuple(party, 0, 0));
		party->getCandidatesArray().push_back(make_tuple(newDistrict,PersonList()));
	}
    
    return true;
}


bool Elections::addPerson(const string& name, int id, int birth_year, int distric_id)
{
	auto p = std::find_if(_voters.begin(), _voters.end(),
		[id](PersonPtr p)->bool { return p->getID() == id; });
		
	if (p != _voters.end() || distric_id > _districts.size() || distric_id <= 0) {
		return false;
	}

	District& district = findDistrict(distric_id);
	PersonPtr newPerson = new Person(name, id, birth_year, &district);
	_voters.push_back(newPerson);
    district.getVoters().push_back(newPerson);
    return true;
}

bool Elections::addParty(const string& name, int candidate_id)
{
	PersonPtr candidate = findPerson(candidate_id);

    if (candidate->isCandidate()) {
        return false;
    }

    Party* newParty = new Party(name, candidate);
    _parties.push_back(newParty);
    candidate->setAsCandidate(newParty);

	for (auto district : _districts) {
		newParty->getCandidatesArray().push_back(make_tuple(district,List<PersonPtr>()));
		district->getPartiesData().push_back(make_tuple(newParty, 0, 0));
	}

    return true;
}

bool Elections::addPersonAsCandidate(int person_id, int party_id, int district_id)
{
	try{
		PersonPtr candidate = findPerson(person_id);
		Party& party = findParty(party_id);
		if (!candidate->isCandidate())
		{
			party.getCandidateList(district_id).push_back(candidate);
			candidate->setAsCandidate(&party);
			return true;
		}
		//else
		//	throw;
		/*
		*
		*/
    }
	catch(const char* msg){
		cout << msg << endl;
	}
    return false;
}

bool Elections::vote(int person_id, int party_id)
{
	PersonPtr person = findPerson(person_id);

    if (person->isVoted()) {
        return false;
    }

    int district_id = person->getDistrictID();
    findDistrict(district_id).vote(party_id);

	Party& party = findParty(party_id);
	party.addTotalVotes(1);
	_votes.push_back(make_tuple(person, &party));
    person->setVote(&party);
	return true;
}

bool Elections::finalEvaluation() {
    
	for (auto party : _parties)
		party->setTotalCandidates(0);
    
	for (auto district : _districts)
		district->evalPartition();
    
    return true;
}

void Elections::sortPartiesArray() {	
	myIterSort(_parties.begin(), _parties.end(), [](Party* p1, Party* p2)->int {
		return p1->getTotalCandidates() > p2->getTotalCandidates();
	});
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
	ElectionsRoundLoader::saveDistricts(out, _districts);
	ElectionsRoundLoader::saveStruct(out, _voters);
	ElectionsRoundLoader::saveStruct(out, _parties);
	ElectionsRoundLoader::saveVotes(out, _votes);
	return true;
}

PersonPtr& Elections::findPerson(int id) {
	auto iter = std::find_if(_voters.begin(), _voters.end(),
		[id](PersonPtr p)->bool { return p->getID() == id; });

	if (iter == _voters.end()) {
		throw "person not found";
		/*
		*/
	}
	return *iter;
}

const PersonPtr& Elections::findPerson(int id) const {
	auto iter = std::find_if(_voters.begin(), _voters.end(),
		[id](PersonPtr p)->bool { return p->getID() == id; });

	if (iter == _voters.end()) {
		throw;
		/*
		*/
	}
	return *iter;
}
District& Elections::findDistrict(int id) {
	auto iter = std::find_if(_districts.begin(), _districts.end(),
		[id](District* d)->bool { return d->getId() == id; });

	if (iter == _districts.end()) {
		throw;
		/*
		*/
	}
	return *(*iter);
}
const District& Elections::findDistrict(int id) const {
	auto iter = std::find_if(_districts.begin(), _districts.end(),
		[id](District* d)->bool { return d->getId() == id; });

	if (iter == _districts.end()) {
		throw;
		/*
		*/
	}
	return *(*iter);
}
Party& Elections::findParty(int id) {
	auto iter = std::find_if(_parties.begin(), _parties.end(),
		[id](Party* p)->bool { return p->getId() == id; });

	if (iter == _parties.end()) {
		throw;
		/*
		*/
	}
	return *(*iter);
}
const Party& Elections::findParty(int id) const {
	auto iter = std::find_if(_parties.begin(), _parties.end(),
		[id](Party* p)->bool { return p->getId() == id; });

	if (iter == _parties.end()) {
		throw;
		/*
		*/
	}
	return *(*iter);
}




}

