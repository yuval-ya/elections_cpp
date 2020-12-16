#include "District.h"
#include "Party.h"
#include "Person.h"
using namespace std;

namespace elections {

	Person::Person(const String& name, int id, int year, const District* district) :
		_name(name), _id(id), _birthYear(year), _district(district),
		_vote(nullptr), _isCandidate(nullptr)
	{
	}

	Person::Person(const Person& p) :
		_name(p._name), _id(p._id), _birthYear(p._birthYear), _district(p._district),
		_vote(p._vote), _isCandidate(p._isCandidate)
	{
	}

	Person::~Person() {
	}

	int Person::getDistrictID() const
	{
		return _district->getId();
	}

	bool Person::setAsCandidate(const Party* p)
	{
		_isCandidate = p;
		return true;
	}
	bool Person::isCandidate() const
	{
		return _isCandidate != nullptr;
	}

	bool Person::isVoted() const
	{
		return _vote != nullptr;
	}
	bool Person::setVote(const Party* p)
	{
		if (!isVoted()) {
			_vote = p;
			return true;
		}
		return false;
	}

	ostream& operator<<(ostream& os, const Person& p) {
		os << "Person Name: " << p.getName() << " | ID: " << p.getID() << " | District: " << p.getDistrictID();
		return os;
	}

}
