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

void Elections::addDistrict(const string& name, int number_of_candidates, DistrictType type)
{
    District* newDistrict;
    
    if (number_of_candidates < 0)
        throw invalid_argument("Invalid candidates number type");

    switch (type) {
        case DistrictType::DIVIDED:
				newDistrict = new DividedDistrict(name, number_of_candidates);
			break;
        case DistrictType::UNIFIED:
				newDistrict = new UnifiedDistrict(name, number_of_candidates);
            break;
        default:
            throw invalid_argument("Invalid district type");
    }

	_districts.push_back(newDistrict);
	for (auto party : _parties) {
		newDistrict->getPartiesData().push_back(make_tuple(party, 0, 0));
		party->getCandidatesArray().push_back(make_tuple(newDistrict,PersonList()));
	}
}


void Elections::addPerson(const string& name,const std::string& id, int birth_year, int distric_id)
{
	auto p = std::find_if(_voters.begin(), _voters.end(),
		[id](PersonPtr p)->bool { return p->getID() == id; });

    if (p != _voters.end()) throw invalid_argument("There is no citizen with the same ID number");
    if (_date.getYear() - birth_year < 18) throw  invalid_argument("This citizen can't vote (under 18)");

	District& district = findDistrict(distric_id);
	PersonPtr newPerson = new Person(name, id, birth_year, &district);
    _voters.push_back(newPerson);
    district.getVoters().push_back(newPerson);
}

void Elections::addParty(const string& name, const string& candidate_id)
{
	PersonPtr candidate = findPerson(candidate_id);
    Party* newParty = new Party(name, candidate);

    try {
        _parties.push_back(newParty);
        candidate->setAsCandidate(newParty);
        for (auto district : _districts) {
            newParty->getCandidatesArray().push_back(make_tuple(district,List<PersonPtr>()));
            district->getPartiesData().push_back(make_tuple(newParty, 0, 0));
        }
    }
    catch (const exception& ex) {
        delete newParty;
        throw ex;
    }
}

void Elections::addPersonAsCandidate(const string& person_id, int party_id, int district_id)
{
    PersonPtr candidate = findPerson(person_id);
    Party& party = findParty(party_id);
    candidate->setAsCandidate(&party);
    party.getCandidateList(district_id).push_back(candidate);
}

void Elections::vote(const string& person_id, int party_id)
{
	PersonPtr person = findPerson(person_id);
    Party& party = findParty(party_id);
    District& district = findDistrict(person->getDistrictID());
    
    person->setVote(&party);
    _votes.push_back(make_tuple(person, &party));
    district.vote(party_id);
	party.addTotalVotes(1);
}

void Elections::finalEvaluation() {
    
	for (auto party : _parties)
		party->setTotalCandidates(0);
    
	for (auto district : _districts)
		district->evalPartition();
    
    
}

void Elections::sortPartiesArray() {
    try {
        myIterSort(_parties.begin(), _parties.end(), [](Party* p1, Party* p2)->int {
            return p1->getTotalCandidates() > p2->getTotalCandidates();
        });
    }
    catch (...) {
        throw runtime_error("Fail to sort parties array");
    }
}

void Elections::load(std::istream& in) {
    try {
        _date.load(in);
        ElectionsRoundLoader::loadDistricts(in, *this);
        ElectionsRoundLoader::loadVoters(in, *this);
        ElectionsRoundLoader::loadParties(in, *this);
        ElectionsRoundLoader::loadVotes(in, *this);
    }
    catch (...)
    {
        for (auto district : _districts)
            delete district;
        
        for (auto party : _parties)
            delete party;
                
        throw;
    }
}

void Elections::save(std::ostream& out) const {
	_date.save(out);
	ElectionsRoundLoader::saveDistricts(out, _districts);
	ElectionsRoundLoader::saveStruct(out, _voters);
	ElectionsRoundLoader::saveStruct(out, _parties);
	ElectionsRoundLoader::saveVotes(out, _votes);
}

PersonPtr& Elections::findPerson(const std::string& id) {
	auto iter = std::find_if(_voters.begin(), _voters.end(),
		[id](PersonPtr p)->bool { return p->getID() == id; });

	if (iter == _voters.end())
        throw invalid_argument("Invalid person ID");

	return *iter;
}

const PersonPtr& Elections::findPerson(const std::string& id) const {
	auto iter = std::find_if(_voters.begin(), _voters.end(),
		[id](PersonPtr p)->bool { return p->getID() == id; });

	if (iter == _voters.end())
        throw invalid_argument("Invalid person ID");
	
	return *iter;
}

District& Elections::findDistrict(int id) {
	auto iter = std::find_if(_districts.begin(), _districts.end(),
		[id](District* d)->bool { return d->getId() == id; });

	if (iter == _districts.end())
        throw invalid_argument("Invalid district ID");
    
	return *(*iter);
}

const District& Elections::findDistrict(int id) const {
	auto iter = std::find_if(_districts.begin(), _districts.end(),
		[id](District* d)->bool { return d->getId() == id; });

	if (iter == _districts.end())
        throw invalid_argument("Invalid district ID");

	return *(*iter);
}

Party& Elections::findParty(int id) {
	auto iter = std::find_if(_parties.begin(), _parties.end(),
		[id](Party* p)->bool { return p->getId() == id; });

	if (iter == _parties.end())
        throw invalid_argument("Invalid party ID");
        
	return *(*iter);
}
const Party& Elections::findParty(int id) const {
	auto iter = std::find_if(_parties.begin(), _parties.end(),
		[id](Party* p)->bool { return p->getId() == id; });

	if (iter == _parties.end())
        throw invalid_argument("Invalid party ID");

	return *(*iter);
}




}

