#pragma once
#include "PersonList.h"
#include "PartyArray.h"
#include "DistrictArray.h"

class Elections
{
	// A class representing a Election round

	private:
		int				_day,
						_month,
						_year;
		PersonList		_voters;
		DistrictArray	_districts;
		PartyArray		_parties;
	public:
		Elections(int day = 1, int month = 1, int year = 2021);
		Elections(const Elections&) = delete;

		bool setDate(int year, int month, int day);
		bool setDay(int day) { _day = day; }
		bool setMonth(int month) { _month = month; }
		bool setYear(int year) { _year = year; }

		int getDay() const { return _day; }
		int getMonth() const { return _month; }
		int getYear() const { return _year; }
		const DistrictArray& getDistricts() { return _districts; }
		const PersonList& getVoters() { return _voters; }
		const PartyArray& getParties() { return _parties; }


		const District& getDistrict(int district_id) const { return _districts[district_id - 1]; }
		const Party& getParty(int party_id) const { return _parties[party_id - 1]; }

		// add new district to the elections
		bool addDistrict(String name, int number_of_candidates);

		// add a new person to the voters list and to the district he belongs
		bool addPerson(String name, int id, int birth_year, int distric_id);

		// add new party to the elections
		bool addParty(String name, int candidate_id);

		// Add a person as a candidate of a party in a given district
		bool addPersonAsCandidate(int person_id, int party_id, int district_id);

		bool vote(int person_id, int party_id);

		void printVoters() const;
		void printDistricts() const;
		void printParties() const;

		// Performs a calculation of all votes in all districts and updates the number of 
		// votes and candidates each party received
		bool finalEvaluation();

		// return a pointer tp Party array and it's size (as an output parameter) 
		// The array is sorted by the order of votes each party received (the winnig party in index 0) 
		Party** getSortedPartiesArr(int& size);
	};
