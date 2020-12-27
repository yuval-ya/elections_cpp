#include "District.h"
#include <iostream>
using namespace std;

namespace elections {

	int District::totalDistricts = 0;

	District::District(const String& name, int numberOfCandidates) :
		_id(++totalDistricts), _name(name), _numberOfCandidates(numberOfCandidates), _numberOfVoters(0), _partiesData(Party::totalParties)
	{
	}

	District::District(const District& other) :
		_id(other._id), _name(other._name), _numberOfCandidates(other._numberOfCandidates),
		_numberOfVoters(other._numberOfVoters), _partiesData(other._partiesData)
	{
	}

	District::District(istream& in) : _numberOfVoters(0)
	{
		totalDistricts++;
		load(in);
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
		os << " | Number of candidates: " << d._numberOfCandidates << " | Type: ";
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

	bool District::save(ostream& out) const{
		out.write(rcastcc(&_id), sizeof(_id));
		_name.save(out);
		out.write(rcastcc(&_numberOfCandidates), sizeof(_numberOfCandidates));
		if (!out.good()) {
			std::cout << "Error writing" << std::endl;
			exit(-1);
		}
		return true;
	}

	bool District::load(istream& in) {
		in.read(rcastc(&_id), sizeof(_id));
		_name.load(in);
		in.read(rcastc(&_numberOfCandidates), sizeof(_numberOfCandidates));
		if (!in.good()) {
			std::cout << "Error reading" << std::endl;
			exit(-1);
		}
		return true;
	}
}