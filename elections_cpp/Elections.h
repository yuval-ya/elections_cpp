#pragma once
#include "Date.h"
#include "Party.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
#include "List.h"
#include "Utilities.h"

#include <string>
#include <vector>
#include <algorithm> 
#include <tuple>

namespace elections {

enum class ElectionsType { RERGULAR = 1, SIMPLE };

class Elections
{
    // A class representing an Elections round
public:
	using PersonList = mySTL::List<PersonPtr>;
	using DistrictArray = std::vector<District*>;
	using PartyArray = std::vector<Party*>;
	using VotesList = mySTL::List<std::tuple<PersonPtr, Party*>>;

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

	PersonPtr& findPerson(const std::string& id);
	const PersonPtr& findPerson(const std::string& id) const;
	District& findDistrict(int id);
	const District& findDistrict(int id) const;
	Party& findParty(int id);
	const Party& findParty(int id) const;
    
    // Add new district to the elections;
    virtual void addDistrict(const std::string& name, int number_of_candidates, DistrictType type);
    
    // Add a new person to the voters list and to the district he belongs
    virtual void addPerson(const std::string& name,const std::string& id, int birth_year, int distric_id);
    
    // Add new party to the elections
    void addParty(const std::string& name, const std::string& candidate_id);
    
    // Add a person as a candidate of a party in a given district
	virtual void addPersonAsCandidate(const std::string& person_id, int party_id, int district_id);
    
    void vote(const std::string& person_id, int party_id);
    
    // Performs a calculation of all votes in all districts and updates the number of
    // votes and candidates each party received
    void finalEvaluation();
    
    // Sort parties array by the order of votes each party received (the winnig party in index 0)
	// using mySTL algorithm
    void sortPartiesArray();

	void load(std::istream& in);
	void save(std::ostream& out) const;
};

}
