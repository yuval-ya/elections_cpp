#include "Menu.h"
#include <iostream>
using namespace std;

namespace elections {

//	void Menu::start(Elections& election)
//	{
//		int choice = 1;
//		int year, month, day;
//		cout << "Enter election's date (year,month,day): " << endl;
//		cin >> year >> month >> day;
//		election.setDate(year, month, day);
//
//		while (choice != 10) {
//			cout << "\nMain menu - choose an option:" << endl;
//			cout << "1.Add District." << endl;
//			cout << "2.Add Citizen." << endl;
//			cout << "3.Add Party." << endl;
//			cout << "4.Add Person as a Party Member." << endl;
//			cout << "5.Print all Districts." << endl;
//			cout << "6.Print all Citizens." << endl;
//			cout << "7.Print all Parties." << endl;
//			cout << "8.Vote." << endl;
//			cout << "9.Show Election results." << endl;
//			cout << "10.Exit.\n" << endl;
//
//			cin >> choice;
//			if (!options(election, choice)) {
//				cout << "\nOops! Something went wrong\nplease try again" << endl;
//			}
//			cin.ignore();
//		}
//	}

	void Menu::test(Elections& election)
	{
		election.addDistrict("A", 5, 0);
		election.addDistrict("B", 10, 0);

		election.addPerson("yuval", 1, 1996, 1);
		election.addPerson("oded", 11, 1996, 2);

		election.addParty("LIKUD", 1);
		election.addParty("AVODA", 11);

		election.addDistrict("C", 3, 0);

		/*election.addPerson("yuval", 1, 1996, 1);*/
		election.addPerson("tamir", 2, 1994, 1);
		election.addPerson("ohad", 3, 1996, 1);
		election.addPerson("nir", 4, 1994, 1);
		election.addPerson("gali", 5, 1996, 1);
		election.addPerson("gil", 6, 1994, 1);
		election.addPerson("itay", 7, 1996, 1);
		election.addPerson("omer", 8, 1997, 1);
		election.addPerson("hadar", 9, 1998, 1);
		election.addPerson("adi", 10, 1992, 1);
		/*election.addPerson("oded", 11, 1996, 2);*/
		election.addPerson("gal", 12, 1996, 2);
		election.addPerson("shaked", 13, 1996, 2);
		election.addPerson("mali", 14, 1996, 2);
		election.addPerson("zohar", 15, 1996, 2);
		election.addPerson("yuval", 16, 1996, 2);
		election.addPerson("tamir", 17, 1994, 2);
		election.addPerson("ohad", 18, 1996, 2);
		election.addPerson("nir", 19, 1994, 2);
		election.addPerson("gali", 20, 1996, 2);
		election.addPerson("gil", 21, 1994, 3);
		election.addPerson("itay", 22, 1996, 3);
		election.addPerson("omer", 23, 1997, 3);
		election.addPerson("hadar", 24, 1998, 3);
		election.addPerson("adi", 25, 1992, 3);
		election.addPerson("oded", 26, 1996, 3);
		election.addPerson("gal", 27, 1996, 3);
		election.addPerson("shaked", 28, 1996, 3);
		election.addPerson("mali", 29, 1996, 3);
		election.addPerson("zohar", 30, 1996, 3);

		//election.addParty("LIKUD", 1);
		//election.addParty("AVODA", 11);
		election.addParty("LIBRMAN", 21);

		election.addPersonAsCandidate(2, 1, 1);
		election.addPersonAsCandidate(3, 1, 1);
		election.addPersonAsCandidate(4, 1, 1);
		election.addPersonAsCandidate(5, 2, 1);
		election.addPersonAsCandidate(6, 2, 1);
		election.addPersonAsCandidate(7, 2, 1);
		election.addPersonAsCandidate(8, 3, 1);
		election.addPersonAsCandidate(9, 3, 1);
		election.addPersonAsCandidate(10, 3, 1);
		election.addPersonAsCandidate(12, 1, 2);
		election.addPersonAsCandidate(13, 1, 2);
		election.addPersonAsCandidate(14, 1, 2);
		election.addPersonAsCandidate(15, 2, 2);
		election.addPersonAsCandidate(16, 2, 2);
		election.addPersonAsCandidate(17, 2, 2);
		election.addPersonAsCandidate(18, 3, 2);
		election.addPersonAsCandidate(19, 3, 2);
		election.addPersonAsCandidate(20, 3, 2);
		election.addPersonAsCandidate(22, 1, 3);
		election.addPersonAsCandidate(23, 1, 3);
		election.addPersonAsCandidate(24, 1, 3);
		election.addPersonAsCandidate(25, 2, 3);
		election.addPersonAsCandidate(26, 2, 3);
		election.addPersonAsCandidate(27, 2, 3);
		election.addPersonAsCandidate(28, 3, 3);
		election.addPersonAsCandidate(29, 3, 3);
		election.addPersonAsCandidate(30, 3, 3);

		election.vote(1, 2);
		election.vote(2, 2);
		election.vote(3, 3);
		election.vote(4, 1);
		election.vote(5, 2);
		election.vote(6, 3);
		election.vote(7, 2);
		election.vote(8, 2);
		election.vote(9, 2);
		election.vote(10, 1);
		election.vote(11, 2);
		election.vote(12, 3);
		election.vote(13, 2);
		election.vote(14, 2);
		election.vote(15, 3);
		election.vote(16, 3);
		election.vote(17, 2);
		election.vote(18, 3);
		election.vote(19, 2);
		election.vote(20, 2);
		election.vote(21, 3);
		election.vote(22, 3);
		election.vote(23, 2);
		election.vote(24, 2);
		election.vote(25, 1);
		election.vote(26, 2);
		election.vote(27, 3);
		election.vote(28, 1);
		election.vote(29, 2);
		election.vote(30, 1);

	}
//
//
//	bool Menu::newDistrict(Elections& election) {
//		char name[MAX_SIZE];
//		int candidates_num, type;
//		cout << "Enter district name: ";
//		cin.ignore();
//		cin.getline(name, MAX_SIZE);
//        cout << "Enter district type: (0 for Divided, 1 for Unified) ";
//        cin >> type;
//		cout << "\nEnter number of candidates: ";
//		cin >> candidates_num;
//		return election.addDistrict(name, candidates_num, type);
//	}
//
//	bool Menu::newParty(Elections& election) {
//		char name[MAX_SIZE];
//		int candidate_id;
//		cout << "Enter party name: ";
//		cin.ignore();
//		cin.getline(name, MAX_SIZE);
//		cout << "Enter first candidate ID: ";
//		cin >> candidate_id;
//		return election.addParty(name, candidate_id);
//	}
//
//	bool Menu::newCitizen(Elections& election) {
//		char name[MAX_SIZE];
//		int id, year, district_id;
//		cout << "Enter name: ";
//		cin.ignore();
//		cin.getline(name, MAX_SIZE);
//		cout << "Enter id: ";
//		cin >> id;
//		cout << "Enter year of birth: ";
//		cin >> year;
//		cout << "Enter district id: ";
//		cin >> district_id;
//		return election.addPerson(name, id, year, district_id);
//	}
//
//	bool Menu::setCitizenAsCandidate(Elections& election) {
//		int candidate_id, party_id, district_id;
//		cout << "Enter candidate ID: ";
//		cin >> candidate_id;
//		cout << "Enter district ID: ";
//		cin >> district_id;
//		cout << "Enter party ID: ";
//		cin >> party_id;
//		return election.addPersonAsCandidate(candidate_id, party_id, district_id);
//	}
//
//
//	bool Menu::vote(Elections& election) {
//		int id, party_id;
//		cout << "Enter ID: ";
//		cin >> id;
//		cout << "Enter party ID: ";
//		cin >> party_id;
//		return election.vote(id, party_id);
//	}
//
//	bool Menu::options(Elections& election, int choice)
//	{
//		bool flag = true;
//		switch (choice) {
//		case 1:
//			flag = newDistrict(election);
//			break;
//		case 2:
//			flag = newCitizen(election);
//			break;
//		case 3:
//			flag = newParty(election);
//			break;
//		case 4:
//			flag = setCitizenAsCandidate(election);
//			break;
//		case 5:
//			election.printDistricts();
//			break;
//		case 6:
//			election.printVoters();
//			break;
//		case 7:
//			election.printParties();
//			break;
//		case 8:
//			flag = vote(election);
//			break;
//		case 9:
//			finish(election);
//			break;
//		case 10:
//			break;
//		default:
//			flag = false;
//			break;
//		}
//		return flag;
//	}
//
//	void Menu::printStatistics(Elections& election) {
//            int numOfDistricts = election.getDistricts().getLength();
//            int numOfParties = election.getParties().getLength();
//
//            for (int i = 1; i <= numOfDistricts; i++)
//            {
//                const District& district = election.getDistricts().get(i);
//
//                const PersonList& winningCandidate = district.getChosenCandidates();
//
//                cout << "============================================ " << endl;
//                cout << district << endl << "Winning candidates: "<< endl << winningCandidate << endl;
//
//                for (int j = 1; j <= numOfParties; j++)
//                {
//                    const Party& party = election.getParties().get(i);
//                    int numOfCandidatesFromParty = district.getPartyCandidatesNum(j);
//                    const PersonList& candidateLst = party.getCandidatesListFromDistrict(i);
//
//                    cout << "\nParty No." << j << endl;
//                    if (candidateLst.getPersonNumber() < numOfCandidatesFromParty)
//                    {    //There are not enough candidates from this district
//                        cout << "*** There are not enough candidates in the party to district" << i << " ***" << endl;
//                    }
//                    candidateLst.printList(numOfCandidatesFromParty);
//                    cout << "Total votes - " << district.getPartyVotes(j) << endl;
//                    cout << "Percentage of votes - " << district.calcPartyPercentInVotes(j) << endl;
//                }
//                cout << "\nPercentage of votes in the district: " << district.calcVotersPercentage() << endl << endl;
//            }
//	}
//
//	void Menu::printResults(Elections& election) {
//		int size = 0;
//		Party** arr = election.getSortedPartiesArr(size);
//
//		cout << "\n~ Results ~" << endl;
//		for (int i = 0; i < size; i++)
//		{
//			const Party& party = *arr[i];
//			cout << "ID: " << party.getId() << " Name: " << party.getName() << endl;
//			cout << "First candidate: " << party.getCandidate().getID() << endl;
//			cout << "Total candidates: " << party.getTotalCandidates() << endl;
//			cout << "Votes count: " << party.getTotalVotes() << endl;
//			cout << "---------------------------- " << endl;
//		}
//		delete[] arr;
//	}
//
//	void Menu::finish(Elections& election) {
//		election.finalEvaluation();
//		printStatistics(election);
//		printResults(election);
//	}
//


}
