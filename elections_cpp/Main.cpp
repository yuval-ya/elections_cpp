//#define _CRTDB_MAP_ALLOC
//#include <crtdbg.h>

#include "Main.h" 
#include "Elections.h"
#include "SimpleElections.h"
#include "Menu.h"

using namespace elections;
using namespace std;




int main(void) {    
	
	int option;
	cout << endl << "Elections Manager -" << endl;
	cout << endl << "Choose an option:" << endl;
	cout << "1.Create new elections round." << endl;
	cout << "2.Load an existing round of elections." << endl;
	cout << "3.Exit." << endl;
	cin >> option;

	if (option == 1)
	{
		int roundType;
		Date date;

		cout << "Choose the type of the elections (1 for Regular , 2 for Simple): ";
		cin >> roundType;
		cout << "Enter the date of the elections (day-month-year): ";
		cin >> date;

		if (roundType == 1) {
			Elections election(date);
			Menu::test(election);
			start(election);
		}
		else if (roundType == 2) {
			int numOfCandidates;
			cout << "Enter the number of candidates that will be in the election: ";
			cin >> numOfCandidates;
			SimpleElections election(numOfCandidates, date);
			Menu::test(election);
			start(election);
		}
		else {
			cout << "Wrong Input!" << endl;
		}
	}
	else if (option == 2)
	{
		char name[MAX_SIZE];
		cout << "Enter file name: ";
		cin >> name;

		// load

	}
	else if(option != 3)
	{
		cout << "Wrong Input!" << endl;
	}

	cout << "Bye!" << endl;


//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtDumpMemoryLeaks();
    return 0;
}

void start(Elections& election)
{
	int choice = 1;
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
		cout << "10.Exit." << endl;
		cout << "11.Save elections to file." << endl;
		cout << "12.Load elections from file.\n" << endl;

		cin >> choice;
		if (!options(election, choice)) {
			cout << "\nOops! Something went wrong\nplease try again" << endl;
		}
		cin.ignore();
	}
}

bool newDistrict(Elections& election) {
    char name[MAX_SIZE];
    int candidates_num, type;
    cout << "Enter district name: ";
    cin.ignore();
    cin.getline(name, MAX_SIZE);
    cout << "Enter district type: (0 for Divided, 1 for Unified) ";
    cin >> type;
    cout << "\nEnter number of candidates: ";
    cin >> candidates_num;
    return election.addDistrict(name, candidates_num, type);
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
		election.getDistricts().print();
		break;
	case 6:
		election.getVoters().printList();
		break;
	case 7:
		election.getParties().print();
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

	cout << endl << "Elections Date: " << election.getDate() << endl << endl;

	for (int i = 1; i <= numOfDistricts; i++)
	{
		const District& district = election.getDistricts().get(i);

		cout << "------------------- District No." << i << " -------------------" << endl;
        cout << district << endl << "Winning candidates: "<< endl;
        district.showWinners(cout);

		for (int j = 1; j <= numOfParties; j++)
		{
			const Party& party = election.getParties().get(j);
			int numOfCandidatesFromParty = district.getPartyCandidatesNum(j);
			const PersonList& candidateList = party.getCandidatesListFromDistrict(i);

			cout << "\nParty No." << j << endl;
			if (candidateList.getPersonNumber() < numOfCandidatesFromParty)
			{	//There are not enough candidates from this district
				cout << "*** There are not enough candidates in the party to district" << i << " ***" << endl;
			}
			candidateList.printList(numOfCandidatesFromParty);
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



