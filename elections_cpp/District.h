#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <string>

#include "List.h"
#include "Party.h"



namespace elections {

    enum class DistrictType { DIVIDED = 1, UNIFIED };

	class District
	{
		// A class representing a District in the elections
	
	using partyTuple = std::tuple<Party*, int, int>; // (party, votes, candidates)
	using PartyDataArray = std::vector<partyTuple>;
	using PersonList = mySTL::List<PersonPtr>;

	protected:
        std::string     _name;
		int				_id;
		int				_numberOfCandidates;
        int				_numberOfVoters;
		PersonList		_voters;
		PartyDataArray  _partiesData; 
		PersonList		_chosenCandidates;

		const partyTuple& getPartyData(int party_id) const;
		partyTuple& getPartyData(int party_id);

	public:
		static int totalDistricts;
		
		District(const std::string& name, int numberOfCandidates);
		District(const District&);
		District(std::istream& in);
		virtual ~District();

		int getId() const { return _id; }
		const std::string& getName() const { return _name; }
		int getNumberOfCandidates() const { return _numberOfCandidates; }
		int getNumberOfVoters() const { return _numberOfVoters; }
		int getCitizensNumber() const { return _voters.size(); }
		
		int getPartyVotes(int party_id) const;
		int getPartyCandidatesNum(int party_id) const;

		PartyDataArray& getPartiesData() { return _partiesData; }
		const PartyDataArray& getPartiesData() const { return _partiesData; }
        PersonList& getVoters() { return _voters; }
        const PersonList& getVoters() const { return _voters; }
		PersonList& getChosenCandidates() { return _chosenCandidates; }
		const PersonList& getChosenCandidates() const { return _chosenCandidates; }

		bool setNumberOfCandidates(int numberOfCandidates);
		bool setName(const std::string& name);
		bool setId(int id);
        
        bool vote(int party_id);

		// Calculation of the percentage of votes in the whole district
		float calcVotersPercentage() const;

		// Calculate the percentage of votes for a particular party out of the total number of votes
		float calcPartyPercentInVotes(int party_id) const;

		// Calculate the number of candidates for a particular party out of the total number of 
		// candidates in the district
		int calcFinalSumOfCandidatesFromParty(int idx) const;

		// Calculates the partition of candidates in the district
        virtual void evalPartition();
        
        virtual std::ostream& showWinners(std::ostream&) const = 0;
        
		virtual void type(std::ostream&) const = 0;

		bool save(std::ostream& out) const;
		bool load(std::istream& in);
        
		friend std::ostream& operator<<(std::ostream& os, const District& d);
	};
}
