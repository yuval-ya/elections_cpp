#pragma once
#include "String.h"
#include "PersonList.h"
#include "DynamicArray.h"
#include "Party.h"

namespace elections {

	class District
	{
		// A class representing a District in the elections

	protected:
		const int		_id;
		String			_name;
		int				_numberOfCandidates;
        int				_numberOfVoters;
		PersonList		_voters;
		DynamicArray	_votesByParties;
		DynamicArray	_candidatePartition;

	public:
		static int totalDistricts;

		District(String name, int number_of_candidates);
		District(const District&);
		~District();

		int getId() const { return _id; }
		const String& getName() const { return _name; }
		int getNumberOfCandidates() const { return _numberOfCandidates; }
		int getNumberOfVoters() const { return _numberOfVoters; }
		int getCitizensNumber() const { return _voters.getPersonNumber(); }
		int getPartyVotes(int party_id) const { return _votesByParties[party_id - 1]; }
		int getPartyCandidatesNum(int party_id) const { return _candidatePartition[party_id - 1]; }

		bool setNumberOfCandidates(int numberOfCandidates);
        bool setName(String name) { _name = name; return true; }

		// Calculation of the percentage of votes in the whole district
		float calcVotersPercentage() const;

		// Calculate the percentage of votes for a particular party out of the total number of votes
		float calcPartyPercentInVotes(int party_id) const;

		// Calculate the number of candidates for a particular party out of the total number of 
		// candidates in the district
		int calcFinalSumOfCandidatesFromParty(int party_id) const;

        
		// Calculates the partition of candidates in the district
        virtual const DynamicArray& evalPartition();
        //
        virtual const PersonList& getElectionResult() const = 0;
		virtual const String type() const = 0;
        
		bool vote(int party_id);

		// Adds a new party for voting and calculation
		bool addPartyToDistrict();

		// add new person to voters list in the district
		PersonPtr addPerson(const Person& p);
		const Person& addPerson(PersonPtr p);

		// search and return person from voters list by id
		PersonPtr getPersonPtr(int idnum);
		const Person& getPerson(int idnum) const;

		friend std::ostream& operator<<(std::ostream& os, const District& d);
	};
}

