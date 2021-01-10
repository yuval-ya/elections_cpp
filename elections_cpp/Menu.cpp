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
//
	void Menu::test(Elections& election)
	{
		election.addDistrict("A", 5, DistrictType::UNIFIED);
		election.addDistrict("B", 10, DistrictType::DIVIDED);

		election.addPerson("yuval", "000000001", 1996, 1);
		election.addPerson("oded", "000000011", 1996, 2);

		election.addParty("LIKUD", "000000001");
		election.addParty("AVODA", "000000011");

		election.addDistrict("C", 3, DistrictType::UNIFIED);

		/*election.addPerson("yuval", 1, 1996, 1);*/
		election.addPerson("tamir", "000000002", 1994, 1);
		election.addPerson("ohad", "000000003", 1996, 1);
		election.addPerson("nir", "000000004", 1994, 1);
		election.addPerson("gali", "000000005", 1996, 1);
		election.addPerson("gil", "000000006", 1994, 1);
		election.addPerson("itay", "000000007", 1996, 1);
		election.addPerson("omer", "000000008", 1997, 1);
		election.addPerson("hadar", "000000009", 1998, 1);
		election.addPerson("adi", "000000010", 1992, 1);
		/*election.addPerson("oded", 11, 1996, 2);*/
		election.addPerson("gal", "000000012", 1996, 2);
		election.addPerson("shaked", "000000013", 1996, 2);
		election.addPerson("mali", "000000014", 1996, 2);
		election.addPerson("zohar", "000000015", 1996, 2);
		election.addPerson("yuval", "000000016", 1996, 2);
		election.addPerson("tamir", "000000017", 1994, 2);
		election.addPerson("ohad", "000000018", 1996, 2);
		election.addPerson("nir", "000000019", 1994, 2);
		election.addPerson("gali", "000000020", 1996, 2);
		election.addPerson("gil", "000000021", 1994, 3);
		election.addPerson("itay", "000000022", 1996, 3);
		election.addPerson("omer", "000000023", 1997, 3);
		election.addPerson("hadar", "000000024", 1998, 3);
		election.addPerson("adi", "000000025", 1992, 3);
		election.addPerson("oded", "000000026", 1996, 3);
		election.addPerson("gal", "000000027", 1996, 3);
		election.addPerson("shaked", "000000028", 1996, 3);
		election.addPerson("mali", "000000029", 1996, 3);
		election.addPerson("zohar", "000000030", 1996, 3);

		//election.addParty("LIKUD", 1);
		//election.addParty("AVODA", 11);
		election.addParty("LIBRMAN", "000000021");

		election.addPersonAsCandidate("000000002", 1, 1);
		election.addPersonAsCandidate("000000003", 1, 1);
		election.addPersonAsCandidate("000000004", 1, 1);
		election.addPersonAsCandidate("000000005", 2, 1);
		election.addPersonAsCandidate("000000006", 2, 1);
		election.addPersonAsCandidate("000000007", 2, 1);
		election.addPersonAsCandidate("000000008", 3, 1);
		election.addPersonAsCandidate("000000009", 3, 1);
		election.addPersonAsCandidate("000000010", 3, 1);
		election.addPersonAsCandidate("000000012", 1, 2);
		election.addPersonAsCandidate("000000013", 1, 2);
		election.addPersonAsCandidate("000000014", 1, 2);
		election.addPersonAsCandidate("000000015", 2, 2);
		election.addPersonAsCandidate("000000016", 2, 2);
		election.addPersonAsCandidate("000000017", 2, 2);
		election.addPersonAsCandidate("000000018", 3, 2);
		election.addPersonAsCandidate("000000019", 3, 2);
		election.addPersonAsCandidate("000000020", 3, 2);
		election.addPersonAsCandidate("000000022", 1, 3);
		election.addPersonAsCandidate("000000023", 1, 3);
		election.addPersonAsCandidate("000000024", 1, 3);
		election.addPersonAsCandidate("000000025", 2, 3);
		election.addPersonAsCandidate("000000026", 2, 3);
		election.addPersonAsCandidate("000000027", 2, 3);
		election.addPersonAsCandidate("000000028", 3, 3);
		election.addPersonAsCandidate("000000029", 3, 3);
		election.addPersonAsCandidate("000000030", 3, 3);

		election.vote("000000001", 2);
		election.vote("000000002", 2);
		election.vote("000000003", 3);
		election.vote("000000004", 1);
		election.vote("000000005", 2);
		election.vote("000000006", 3);
		election.vote("000000007", 2);
		election.vote("000000008", 2);
		election.vote("000000009", 2);
		election.vote("000000010", 1);
		election.vote("000000011", 2);
		election.vote("000000012", 3);
		election.vote("000000013", 2);
		election.vote("000000014", 2);
		election.vote("000000015", 3);
		election.vote("000000016", 3);
		election.vote("000000017", 2);
		election.vote("000000018", 3);
		election.vote("000000019", 2);
		election.vote("000000020", 2);
		election.vote("000000021", 3);
		election.vote("000000022", 3);
		election.vote("000000023", 2);
		election.vote("000000024", 2);
		election.vote("000000025", 1);
		election.vote("000000026", 2);
		election.vote("000000027", 3);
		election.vote("000000028", 1);
		election.vote("000000029", 2);
		election.vote("000000030", 1);

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
