#pragma once
#include "Date.h"
#include "PersonList.h"
#include "PartyArray.h"
#include "DistrictArray.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
#include "VotesList.h"

namespace elections {

enum class ElectionsType { RERGULAR = 1, SIMPLE };

class Elections
{
    // A class representing an Elections round
    
protected:
	Date			_date;
    PersonList		_voters;
    DistrictArray	_districts;
    PartyArray		_parties;
	VotesList		_votes;

public:
	Elections(const Date&);
    Elections(const Elections&) = delete;
	Elections(std::istream& in);
	virtual ~Elections();

	bool setDate(const Date& date) { _date = date; return true; }

	const Date& getDate() const { return _date; }
	Date& getDate() { return _date; }
    const DistrictArray& getDistricts() const { return _districts; }
    DistrictArray& getDistricts() { return _districts; }
    const PersonList& getVoters() const { return _voters; }
    PersonList& getVoters() { return _voters; }
    const PartyArray& getParties() const { return _parties; }
    PartyArray& getParties() { return _parties; }
	const VotesList& getVotes() const { return _votes; }
	VotesList& getVotes() { return _votes; }
    
    // add new district to the elections; type : 0 = DividedDistrict, 1 = UnifiedDistrict
    virtual bool addDistrict(const String& name, int number_of_candidates, DistrictType type);
    
    // add a new person to the voters list and to the district he belongs
    virtual bool addPerson(const String& name, int id, int birth_year, int distric_id);
    
    // add new party to the elections
    bool addParty(const String& name, int candidate_id);
    
    // Add a person as a candidate of a party in a given district
	virtual bool addPersonAsCandidate(int person_id, int party_id, int district_id);
    
    bool vote(int person_id, int party_id);
    
    // Performs a calculation of all votes in all districts and updates the number of
    // votes and candidates each party received
    bool finalEvaluation();
    
    // return a pointer tp Party array and it's size (as an output parameter)
    // The array is sorted by the order of votes each party received (the winnig party in index 0)
    Party** getSortedPartiesArr(int& size);

	bool load(std::istream& in);
	bool save(std::ostream& out) const;
};

}
