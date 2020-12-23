#pragma once
#include "String.h"
#include "PersonList.h"
#include "PartyDataArray.h"

namespace elections {

    enum class DistrictType { DIVIDED = 1, UNIFIED };

	class District
	{
		// A class representing a District in the elections

	protected:
        String          _name;
		int				_id;
		int				_numberOfCandidates;
        int				_numberOfVoters;
		PersonList		_voters;
        PartyDataArray  _partiesData;
		PersonList		_chosenCandidates;

	public:
		static int totalDistricts;
		
		District(const String& name, int number_of_candidates);
		District(const District&);
		virtual ~District();

		int getId() const { return _id; }
		const String& getName() const { return _name; }
		int getNumberOfCandidates() const { return _numberOfCandidates; }
		int getNumberOfVoters() const { return _numberOfVoters; }
		int getCitizensNumber() const { return _voters.getPersonNumber(); }
		int getPartyVotes(int party_id) const { return _partiesData.get(party_id).votes; }
		int getPartyCandidatesNum(int party_id) const { return _partiesData.get(party_id).candidates; }
		PartyDataArray& getPartiesData() { return _partiesData; }
		const PartyDataArray& getPartiesData() const { return _partiesData; }   
        PersonList& getVoters() { return _voters; }
        const PersonList& getVoters() const { return _voters; }
		PersonList& getChosenCandidates() { return _chosenCandidates; }
		const PersonList& getChosenCandidates() const { return _chosenCandidates; }

		bool setNumberOfCandidates(int numberOfCandidates);
		bool setName(const String& name);
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
        
		friend std::ostream& operator<<(std::ostream& os, const District& d);
	};
}
