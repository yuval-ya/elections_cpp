#include "District.h"
using namespace std;

namespace elections {

	int District::totalDistricts = 0;

	District::District(String name, int numberOfCandidates) :
		_id(++totalDistricts), _name(name), _numberOfCandidates(numberOfCandidates), _numberOfVoters(0)
	{
	}

	District::District(const District& d) :
		_id(d._id), _name(d._name), _numberOfCandidates(d._numberOfCandidates),
		_votesByParties(Party::totalParties), _candidatePartition(Party::totalParties)
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
		return (_votesByParties[party_id - 1] / static_cast<float>(_numberOfVoters)) * 100;
	}

	int District::calcFinalSumOfCandidatesFromParty(int party_id) const {
		if (_numberOfVoters == 0)
		{
			// division by zero error!
			return 0;
		}
		int res = static_cast<int>((_votesByParties[party_id - 1] / static_cast<float>(_numberOfVoters)) * _numberOfCandidates);
		return res;
	}

	PersonPtr District::addPerson(const Person& p) {
		return _voters.addPerson(p);
	}
	const Person& District::addPerson(PersonPtr p) {
		return _voters.addPerson(p);
	}

	PersonPtr District::getPersonPtr(int idnum) {
		return _voters.getPersonPtr(idnum);
	}
	const Person& District::getPerson(int idnum) const {
		return _voters.getPerson(idnum);
	}

	ostream& operator<<(ostream& os, const District& d) {
		os << "District ID: " << d._id << " | Name: " << d._name << " | Number of candidates: " << d._numberOfCandidates;
		return os;
	}

	bool District::vote(int party_id) {
		_votesByParties[party_id - 1]++;
		_numberOfVoters++;
		return true;
	}

	bool District::setNumberOfCandidates(int numberOfCandidates) {
		_numberOfCandidates = numberOfCandidates;
		return true;
	}

	bool District::addPartyToDistrict()
	{
		return _votesByParties.add() && _candidatePartition.add();
	}

    const DynamicArray& District::evalPartition()
    {
        int parties_num = _votesByParties.getLength(), count = 0;

        for (int i = 0; i < parties_num; i++) {
            _candidatePartition[i] = calcFinalSumOfCandidatesFromParty(i + 1);
            count += _candidatePartition[i];
        }

        if (_numberOfCandidates > count) {
            int i = _votesByParties.getMax();
            _candidatePartition[i] += _numberOfCandidates - count;
        }
        
        return _candidatePartition;
    }
}
