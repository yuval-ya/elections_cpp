#pragma once
#include "String.h"
#include "CandidatesArray.h"

namespace elections {
class District;

class Party
{
	// A class representing a Party in the elections

private:
	const int			_id;
	String				_name;
    PersonPtr		    _firstCandidate;
	int					_totalCandidates,
						_totalVotes;
	CandidatesArray		_candidates;
	
public:
	static int totalParties;

	Party(const String& name, PersonPtr candidate);
	Party(const Party& p);
	~Party();

	int getId() const { return _id; }
	const String& getName() const { return _name; }
	const PersonList& getCandidatesListFromDistrict(int district_id) const { return _candidates.get(district_id); }
	const CandidatesArray& getCandidatesArray() const { return _candidates; }
	PersonPtr getCandidatePtr() { return _firstCandidate; }
    const Person& getCandidate() const { return *_firstCandidate; }
    int getTotalCandidates() const { return _totalCandidates; }
    int getTotalVotes() const { return _totalVotes; }

    bool setTotalCandidates(int val);
    bool setFirstCandidate(PersonPtr candidate);

	// add a new candidate to the candidate list according to the district id
	void addCandidate(PersonPtr p, int district_id);

	// add a new empty list to Candidates Array
	void addDistrictToCandidatesArr();

	// add value to the total number of candidates the party get in the elections 
	void addTotalCandidates(int val) { _totalCandidates += val; }
	void addTotalVotes(int val) { _totalVotes += val; }

	friend std::ostream& operator<<(std::ostream& os, const Party& p);
};

}
