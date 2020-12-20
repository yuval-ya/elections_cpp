#include "District.h"
#include <iostream>
using namespace std;

namespace elections {

	int District::totalDistricts = 0;

	District::District(const String& name, int numberOfCandidates) :
		_id(++totalDistricts), _name(name), _numberOfCandidates(numberOfCandidates), _numberOfVoters(0), _partiesData(Party::totalParties)
	{
	}

	District::District(const District& d) :
		_id(d._id), _name(d._name), _numberOfCandidates(d._numberOfCandidates), _partiesData(d._partiesData)
	{
		_numberOfVoters = d.getNumberOfVoters();
	}

	District::~District() {
	}

	float District::calcVotersPercentage() const
	{
		int citizenNumber = getCitizensNumber();
		if (citizenNumber == 0)
		{
			// division by zero error!
			return 0;
		}
		return _numberOfVoters / static_cast<float>(citizenNumber) * 100;
	}

	float District::calcPartyPercentInVotes(int party_id) const
	{
		if (_numberOfVoters == 0)
		{
			// division by zero error!
			return 0;
		}
		return (_partiesData.get(party_id).votes / static_cast<float>(_numberOfVoters)) * 100;
	}

	int District::calcFinalSumOfCandidatesFromParty(int idx) const {
		if (_numberOfVoters == 0)
		{
			// division by zero error!
			return 0;
		}
		int res = static_cast<int>((_partiesData[idx].votes / static_cast<float>(_numberOfVoters)) * _numberOfCandidates);
		return res;
	}


	ostream& operator<<(ostream& os, const District& d) {
		os << "District ID: " << d._id << " | Name: " << d._name;
        os << " | Number of candidates: " << d._numberOfCandidates << " | Type: " ;
        d.type(os);
		return os;
	}

	bool District::vote(int party_id) {
		_partiesData.get(party_id).votes++;
		_numberOfVoters++;
		return true;
	}

	bool District::setNumberOfCandidates(int numberOfCandidates) {
		_numberOfCandidates = numberOfCandidates;
		return true;
	}

	bool District::setName(const String& name)
	{
		_name = name;
		return true;
	}

	bool District::setId(int id) {
		_id = id;
		return true;
	}

    void District::evalPartition()
    {
        int parties_num = _partiesData.getLength(), count = 0;
        for (int i = 0; i < parties_num; i++) {
            _partiesData[i].candidates = calcFinalSumOfCandidatesFromParty(i);
            count += _partiesData[i].candidates;
        }

        if (_numberOfCandidates > count) {
            int id = _partiesData.getPartyIdWithMaxVotes();
            _partiesData.get(id).candidates += _numberOfCandidates - count;
        }
        _partiesData.sortArrayByCandidates();
    }
}
