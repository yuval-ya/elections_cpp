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

	Person::Person(istream& in) :
		_district(nullptr), _vote(nullptr), _isCandidate(nullptr)
	{
		load(in);
	}

	Person::Person(istream& in, int& districtID, int& vote, int& candidate) :
		_district(nullptr), _vote(nullptr), _isCandidate(nullptr)
	{
		load(in);
		in.read(rcastc(&districtID), sizeof(districtID));
		in.read(rcastc(&vote), sizeof(vote));
		in.read(rcastc(&candidate), sizeof(candidate));
	}

	Person::~Person() {
	}

	bool Person::setName(const String& name)
	{
		_name = name;
		return true;
	}

	bool Person::setId(int id) {
		_id = id;
		return true;
	}
	bool Person::setBirthYear(int birthYear) {
		_birthYear = birthYear;
		return true;
	}

	bool Person::setDistrict(const District* district) {
		_district = district;
		return true;
	}

	int Person::getDistrictID() const
	{
        int id = _district->getId();
        return id;
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

	bool Person::load(std::istream& in) {
		in.read(rcastc(&_id), sizeof(_id));
		_name.load(in);
		in.read(rcastc(&_birthYear), sizeof(_birthYear));
		return true;
	}

	bool Person::save(std::ostream& out) const {
		int district, vote = 0, candidate = 0;

		district = _district->getId();
		if (isVoted())
			vote = _vote->getId();
		if (isCandidate())
			candidate = _isCandidate->getId();

		out.write(rcastcc(&_id), sizeof(_id));
		_name.save(out);
		out.write(rcastcc(&_birthYear), sizeof(_birthYear));
		out.write(rcastcc(&district), sizeof(district));
		out.write(rcastcc(&vote), sizeof(vote));
		out.write(rcastcc(&candidate), sizeof(candidate));

		return true;
	}
}
