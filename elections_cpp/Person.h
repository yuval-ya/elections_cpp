#pragma once
#include <string>
#include <iostream>

namespace elections {

	class District;
	class Party;		// forward declaration 

	class Person
	{
		// A class representing a citizen in the elections

	private:
		int					_id;
		std::string			_name;
		int					_birthYear;
		const District*		_district;
		const Party*		_vote;
		const Party*		_isCandidate;
        
        static const int ID_SIZE = 9;

	public:
		Person(const std::string&, int id, int year, const District* district);
		Person(const Person& p);
		Person(std::istream& in);
		Person(std::istream& in, int& districtID, int& vote, int& candidate);
		~Person();

		const std::string& getName() const { return _name; }
		int getID() const { return _id; };
		int getYear() const { return _birthYear; };
		int getDistrictID() const;

		void setName(const std::string& name);
		void setId(int id);
		void setBirthYear(int birthYear);
		void setDistrict(const District* district);

		// set the citizen as a candidate of a party by adding the pointer to the party
		void setAsCandidate(const Party* p);

		// returns if the citizen already voted in the current elections
		bool isVoted() const;

		// save the party that the citizen vote for 
		void setVote(const Party* p);

		friend std::ostream& operator<<(std::ostream& os, const Person& p);

		void load(std::istream& in);
		void save(std::ostream& out) const;

	};

}
