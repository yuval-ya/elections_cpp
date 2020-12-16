//#define _CRTDB_MAP_ALLOC
//#include <crtdbg.h>

#include <iostream>
using namespace std;

#include "Main.h" 
#include "Elections.h"
using namespace elections;

#include "Menu.h"


int main(void) {

	{
		Elections election;	

		Menu::test(election);
		start(election);
	}
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtDumpMemoryLeaks();
    return 0;
}

void start(Elections& election)
{
	int choice = 1;
	int year, month, day;
	do {
		cout << "Enter election's date (year,month,day): " << endl;
		cin >> year >> month >> day;
	} while (!election.setDate(year, month, day));

	while (choice != 10) {
		cout << "\nMain menu - choose an option:" << endl;
		cout << "1.Add District." << endl;
		cout << "2.Add Citizen." << endl;
		cout << "3.Add Party." << endl;
		cout << "4.Add Person as a Party Member." << endl;
		cout << "5.Print all Districts." << endl;
		cout << "6.Print all Citizens." << endl;
		cout << "7.Print all Parties." << endl;
		cout << "8.Vote." << endl;
		cout << "9.Show Election results." << endl;
		cout << "10.Exit.\n" << endl;

		cin >> choice;
		if (!options(election, choice)) {
			cout << "\nOops! Something went wrong\nplease try again" << endl;
		}
		cin.ignore();
	}
}

bool newDistrict(Elections& election) {
	char name[MAX_SIZE];
	int candidates_num;
	cout << "Enter district name: ";
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Enter number of candidates: ";
	cin >> candidates_num;
	return election.addDistrict(name, candidates_num);
}

bool newParty(Elections& election) {
	char name[MAX_SIZE];
	int candidate_id;
	cout << "Enter party name: ";
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Enter first candidate ID: ";
	cin >> candidate_id;
	return election.addParty(name, candidate_id);
}

bool newCitizen(Elections& election) {
	char name[MAX_SIZE];
	int id, year, district_id;
	cout << "Enter name: ";
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Enter id: ";
	cin >> id;
	cout << "Enter year of birth: ";
	cin >> year;
	cout << "Enter district id: ";
	cin >> district_id;
	return election.addPerson(name, id, year, district_id);
}

bool setCitizenAsCandidate(Elections& election) {
	int candidate_id, party_id, district_id;
	cout << "Enter candidate ID: ";
	cin >> candidate_id;
	cout << "Enter district ID: ";
	cin >> district_id;
	cout << "Enter party ID: ";
	cin >> party_id;
	return election.addPersonAsCandidate(candidate_id, party_id, district_id);
}

bool vote(Elections& election) {
	int id, party_id;
	cout << "Enter ID: ";
	cin >> id;
	cout << "Enter party ID: ";
	cin >> party_id;
	return election.vote(id, party_id);
}

bool options(Elections& election, int choice)
{
	bool flag = true;
	switch (choice) {
	case 1:
		flag = newDistrict(election);
		break;
	case 2:
		flag = newCitizen(election);
		break;
	case 3:
		flag = newParty(election);
		break;
	case 4:
		flag = setCitizenAsCandidate(election);
		break;
	case 5:
		election.printDistricts();
		break;
	case 6:
		election.printVoters();
		break;
	case 7:
		election.printParties();
		break;
	case 8:
		flag = vote(election);
		break;
	case 9:
		finish(election);
		break;
	case 10:
		break;
	default:
		flag = false;
		break;
	}
	return flag;
}

void printStatistics(Elections& election) {
	int numOfDistricts = election.getDistricts().getLength();
	int numOfParties = election.getParties().getLength();

	for (int i = 1; i <= numOfDistricts; i++)
	{
		const District& district = election.getDistrict(i);
		int winnerPartyInDistrict = district.getWinnerParty();
        const Person& winningCandidate = election.getParty(winnerPartyInDistrict).getCandidate();

		cout << "============================================ " << endl;
		cout << district << endl << "Winning candidate: " << winningCandidate << endl;

		for (int j = 1; j <= numOfParties; j++)
		{
			const Party& party = election.getParty(j);
			int numOfCandidatesFromParty = district.getPartyCandidatesNum(j);
			const PersonList& candidateLst = party.getCandidatesListFromDistrict(i);

			cout << "\nParty No." << j << endl;
			if (candidateLst.getPersonNumber() < numOfCandidatesFromParty)
			{	//There are not enough candidates from this district
				cout << "*** There are not enough candidates in the party to district" << i << " ***" << endl;
			}
			candidateLst.printList(numOfCandidatesFromParty);
			cout << "Total votes - " << district.getPartyVotes(j) << endl;
			cout << "Percentage of votes - " << district.calcPartyPercentInVotes(j) << endl;
		}
		cout << "\nPercentage of votes in the district: " << district.calcVotersPercentage() << endl << endl;
	}
}

void printResults(Elections& election) {
	int size = 0;
	Party** arr = election.getSortedPartiesArr(size);

	cout << "\n~ Results ~" << endl;
	for (int i = 0; i < size; i++)
	{
		const Party& party = *arr[i];
		cout << "ID: " << party.getId() << " Name: " << party.getName() << endl;
		cout << "First candidate: " << party.getCandidate().getID() << endl;
		cout << "Total candidates: " << party.getTotalCandidates() << endl;
		cout << "Votes count: " << party.getTotalVotes() << endl;
		cout << "---------------------------- " << endl;
	}
	delete[] arr;
}

void finish(Elections& election) {
	election.finalEvaluation();
	printStatistics(election);
	printResults(election);
}



