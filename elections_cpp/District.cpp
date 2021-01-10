#include "District.h"
#include "Utilities.h"


#include <iostream>

using namespace std;
using namespace mySTL;

namespace elections {

	int District::totalDistricts = 0;

	District::District(const string& name, int numberOfCandidates) :
		_id(++totalDistricts), _name(name), _numberOfCandidates(numberOfCandidates), _numberOfVoters(0)
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
		int citizenNumber = _voters.size();
		if (citizenNumber == 0)
            throw runtime_error("Attempt to divide by zero");

		return _numberOfVoters / static_cast<float>(citizenNumber) * 100;
	}

	float District::calcPartyPercentInVotes(int party_id) const
	{
		if (_numberOfVoters == 0)
            throw runtime_error("Attempt to divide by zero");
        
		return (getPartyVotes(party_id) / static_cast<float>(_numberOfVoters)) * 100;
	}

	int District::calcFinalSumOfCandidatesFromParty(int idx) const {
        if (_numberOfVoters == 0)
            throw runtime_error("Attempt to divide by zero");
        
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
            throw invalid_argument("Invalid party ID");
        
		return *tp;
	}
	District::partyTuple& District::getPartyData(int party_id) {
		auto tp = find_if(_partiesData.begin(), _partiesData.end(),
			[party_id](partyTuple partyTp)->bool { return get<0>(partyTp)->getId() == party_id; });

        if (tp == _partiesData.end())
            throw invalid_argument("Invalid party ID");

		return *tp;
	}


	ostream& operator<<(ostream& os, const District& d) {
		os << "District ID: " << d._id << " | Name: " << d._name;
		os << " | Number of candidates: " << d._numberOfCandidates << " | Type: ";
		d.type(os);
		return os;
	}

	void District::vote(int party_id) {
		get<1>(getPartyData(party_id))++;
		_numberOfVoters++;
	}

	void District::setNumberOfCandidates(int numberOfCandidates) {
		_numberOfCandidates = numberOfCandidates;
	}

	void District::setName(const string& name) {
		_name = name;
	}

	void District::setId(int id) {
		_id = id;
	}

	void District::evalPartition()
	{
		int parties_num = _partiesData.size(), count = 0;
		for (int i = 0; i < parties_num; i++) {
            try {
                get<2>(_partiesData[i]) = calcFinalSumOfCandidatesFromParty(i);
            }
            catch (runtime_error& ex) {
                get<2>(_partiesData[i]) = 0;
            }
			count += get<2>(_partiesData[i]);
		}

		if (_numberOfCandidates > count) {
			auto max = max_element(_partiesData.begin(), _partiesData.end(),
				[](partyTuple p1, partyTuple p2)->int { return get<1>(p1) < get<1>(p2); });
            
			if (max == _partiesData.end())
				throw runtime_error("There are no parties in the elections - can't evaluate the results");
            
			get<2>(*max) += _numberOfCandidates - count;
		}

		myIterSort(_partiesData.begin(), _partiesData.end(), 
			[](partyTuple p1, partyTuple p2)->int { return get<2>(p2) < get<2>(p1); });
	}

	void District::save(ostream& out) const{
		out.write(rcastcc(&_id), sizeof(_id));
		StringLoader::save(out, _name);
		out.write(rcastcc(&_numberOfCandidates), sizeof(_numberOfCandidates));
	}

	void District::load(istream& in) {
		in.read(rcastc(&_id), sizeof(_id));
		_name = StringLoader::load(in);
		in.read(rcastc(&_numberOfCandidates), sizeof(_numberOfCandidates));
	}
}
