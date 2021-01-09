#include "District.h"
#include "Utilities.h"
#include "StringLoader.h"

#include <iostream>

using namespace std;
using namespace mySTL;

namespace elections {

	int District::totalDistricts = 0;

	District::District(const string& name, int numberOfCandidates) :
		_id(++totalDistricts), _name(name), _numberOfCandidates(numberOfCandidates), _numberOfVoters(0), _partiesData(Party::totalParties)
	{
	}

	District::District(const District& other) :
		_id(other._id), _name(other._name), _numberOfCandidates(other._numberOfCandidates),
		_numberOfVoters(other._numberOfVoters), _partiesData(other._partiesData),
		_voters(other._voters), _chosenCandidates(other._chosenCandidates)
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
		return (getPartyVotes(party_id) / static_cast<float>(_numberOfVoters)) * 100;
	}

	int District::calcFinalSumOfCandidatesFromParty(int idx) const {
		if (_numberOfVoters == 0)
		{
			// division by zero error!
			return 0;
		}
		int res = static_cast<int>((get<1>(_partiesData[idx]) / static_cast<float>(_numberOfVoters)) * _numberOfCandidates);
		return res;
	}

	int District::getPartyVotes(int party_id) const {
		return get<1>(getPartyData(party_id));
	}

	int District::getPartyCandidatesNum(int party_id) const {
		return get<2>(getPartyData(party_id));
	}

	const District::partyTuple& District::getPartyData(int party_id) const {
		auto tp = find_if(_partiesData.begin(), _partiesData.end(), 
			[party_id](partyTuple partyTp)->bool { return get<0>(partyTp)->getId() == party_id; });
		
		if (tp == _partiesData.end())
			throw;
		/*
		*
		*
		*
		*/
		return *tp;
	}
	District::partyTuple& District::getPartyData(int party_id) {
		auto tp = find_if(_partiesData.begin(), _partiesData.end(),
			[party_id](partyTuple partyTp)->bool { return get<0>(partyTp)->getId() == party_id; });

		if (tp == _partiesData.end())
			throw;
		/*
		*
		*
		*
		*/
		return *tp;
	}


	ostream& operator<<(ostream& os, const District& d) {
		os << "District ID: " << d._id << " | Name: " << d._name;
		os << " | Number of candidates: " << d._numberOfCandidates << " | Type: ";
		d.type(os);
		return os;
	}

	bool District::vote(int party_id) {
		get<1>(getPartyData(party_id))++;
		_numberOfVoters++;
		return true;
	}

	bool District::setNumberOfCandidates(int numberOfCandidates) {
		_numberOfCandidates = numberOfCandidates;
		return true;
	}

	bool District::setName(const string& name)
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
		int parties_num = _partiesData.size(), count = 0;

		for (int i = 0; i < parties_num; i++) {	
			get<2>(_partiesData[i]) = calcFinalSumOfCandidatesFromParty(i);
			count += get<2>(_partiesData[i]);
		}

		if (_numberOfCandidates > count) {
			auto max = max_element(_partiesData.begin(), _partiesData.end(),
				[](partyTuple p1, partyTuple p2)->int { return myCmp(get<1>(p1), get<1>(p2)); });
			if (max == _partiesData.end())
				throw;
			/*
			*
			*/

			get<2>(*max) += _numberOfCandidates - count;
		}

		sort(_partiesData.begin(), _partiesData.end(), 
			[](partyTuple p1, partyTuple p2)->int { return myCmp(get<2>(p2), get<2>(p1)); });
	}

	bool District::save(ostream& out) const{
		out.write(rcastcc(&_id), sizeof(_id));
		StringLoader::save(out, _name);
		out.write(rcastcc(&_numberOfCandidates), sizeof(_numberOfCandidates));
		if (!out.good()) {
			std::cout << "Error writing" << std::endl;
			exit(-1);
		}
		return true;
	}

	bool District::load(istream& in) {
		in.read(rcastc(&_id), sizeof(_id));
		_name = StringLoader::load(in);
		in.read(rcastc(&_numberOfCandidates), sizeof(_numberOfCandidates));
		if (!in.good()) {
			std::cout << "Error reading" << std::endl;
			exit(-1);
		}
		return true;
	}
}