#pragma once
#include "String.h"
#include <iostream>

namespace elections {

	class District;
	class Party;		// forward declaration 

	class Person
	{
		// A class representing a citizen in the elections

	private:
		int					_id;
		String				_name;
		int					_birthYear;
		const District*		_district;
		const Party*		_vote;
		const Party*		_isCandidate;

	public:
		Person(const String&, int id, int year, const District* district);
		Person(const Person& p);
		Person(std::istream& in);
		Person(std::istream& in, int& districtID, int& vote, int& candidate);
		~Person();

		const String& getName() const { return _name; }
		int getID() const { return _id; };
		int getYear() const { return _birthYear; };
		int getDistrictID() const;

		bool setName(const String& name);
		bool setId(int id);
		bool setBirthYear(int birthYear);
		bool setDistrict(const District* district);

		// set the citizen as a candidate of a party by adding the pointer to the party
		bool setAsCandidate(const Party* p);

		// returns if the citizen is a candidate of some party
		bool isCandidate() const;

		// returns if the citizen already voted in the current elections
		bool isVoted() const;

		// save the party that the citizen vote for 
		bool setVote(const Party* p);

		friend std::ostream& operator<<(std::ostream& os, const Person& p);

		bool load(std::istream& in);
		bool save(std::ostream& out) const;

	};

}
