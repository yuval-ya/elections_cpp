#include <iostream>
using namespace std;

#include "Main.h" 
#include "Elections.h"

int main(void) {
	Elections election;

	/*election.add_district("A", 4);
    election.add_district("B", 5);
	election.add_district("C", 3);
    
    election.add_person("yuval", 1, 1996, 1);
	election.add_person("tamir", 2, 1994, 1);
	election.add_person("ohad", 3, 1996, 1);
	election.add_person("nir", 4, 1994, 1);
	election.add_person("gali", 5, 1996, 1);
	election.add_person("gil", 6, 1994, 1);
	election.add_person("itay", 7, 1996, 1);
	election.add_person("omer", 8, 1997, 1);
	election.add_person("hadar", 9, 1998, 1);
	election.add_person("adi", 10, 1992, 1);
    election.add_person("oded", 11, 1996, 2);
	election.add_person("gal", 12, 1996, 2);
	election.add_person("shaked", 13, 1996, 2);
	election.add_person("mali", 14, 1996, 2);
	election.add_person("zohar", 15, 1996, 2);
	election.add_person("yuval", 16, 1996, 2);
	election.add_person("tamir", 17, 1994, 2);
	election.add_person("ohad", 18, 1996, 2);
	election.add_person("nir", 19, 1994, 2);
	election.add_person("gali", 20, 1996, 2);
	election.add_person("gil", 21, 1994, 3);
	election.add_person("itay", 22, 1996, 3);
	election.add_person("omer", 23, 1997, 3);
	election.add_person("hadar", 24, 1998, 3);
	election.add_person("adi", 25, 1992, 3);
	election.add_person("oded", 26, 1996, 3);
	election.add_person("gal", 27, 1996, 3);
	election.add_person("shaked", 28, 1996, 3);
	election.add_person("mali", 29, 1996, 3);
	election.add_person("zohar", 30, 1996, 3);

	election.add_party("LIKUD", 1);
	election.add_party("AVODA", 11);
	election.add_party("LIBRMAN", 21);

	election.add_person_as_candidate(2, 1, 1);
	election.add_person_as_candidate(3, 1, 1);
	election.add_person_as_candidate(4, 1, 1);
    election.add_person_as_candidate(5, 2, 1);
	election.add_person_as_candidate(6, 2, 1);
	election.add_person_as_candidate(7, 2, 1);
	election.add_person_as_candidate(8, 3, 1);
	election.add_person_as_candidate(9, 3, 1);
	election.add_person_as_candidate(10, 3, 1);
	election.add_person_as_candidate(12, 1, 2);
	election.add_person_as_candidate(13, 1, 2);
	election.add_person_as_candidate(14, 1, 2);
	election.add_person_as_candidate(15, 2, 2);
	election.add_person_as_candidate(16, 2, 2);
	election.add_person_as_candidate(17, 2, 2);
	election.add_person_as_candidate(18, 3, 2);
	election.add_person_as_candidate(19, 3, 2);
	election.add_person_as_candidate(20, 3, 2);
	election.add_person_as_candidate(22, 1, 3);
	election.add_person_as_candidate(23, 1, 3);
	election.add_person_as_candidate(24, 1, 3);
	election.add_person_as_candidate(25, 2, 3);
	election.add_person_as_candidate(26, 2, 3);
	election.add_person_as_candidate(27, 2, 3);
	election.add_person_as_candidate(28, 3, 3);
	election.add_person_as_candidate(29, 3, 3);
	election.add_person_as_candidate(30, 3, 3);

	election.vote(1, 1);
	election.vote(2, 2);
	election.vote(3, 3);
	election.vote(4, 1);
	election.vote(5, 2);
	election.vote(6, 3);
	election.vote(7, 1);
	election.vote(8, 2);
	election.vote(9, 3);
	election.vote(10, 1);
	election.vote(11, 2);
	election.vote(12, 3);
	election.vote(13, 1);
	election.vote(14, 2);
	election.vote(15, 3);
	election.vote(16, 1);
	election.vote(17, 2);
	election.vote(18, 3);
	election.vote(19, 1);
	election.vote(20, 2);
	election.vote(21, 3);
	election.vote(22, 1);
	election.vote(23, 2);
	election.vote(24, 3);
	election.vote(25, 1);
	election.vote(26, 2);
	election.vote(27, 3);
	election.vote(28, 1);
	election.vote(29, 2);
	election.vote(30, 3);*/

	start(election);

    return 0;
}


void start(Elections& election)
{
	int choice = 1;
	int year, month, day;
	cout << "Enter election's date (year,month,day): " << endl;
	cin >> year >> month >> day;
	election.setDate(year, month, day);

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

bool new_district(Elections& election) {
	char name[MAX_SIZE];
	int candidates_num;
	cout << "Enter district name: ";
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Enter number of candidates: ";
	cin >> candidates_num;
	return election.add_district(name, candidates_num);
}

bool new_party(Elections& election) {
	char name[MAX_SIZE];
	int candidate_id;
	cout << "Enter party name: ";
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Enter first candidate ID: ";
	cin >> candidate_id;
	return election.add_party(name, candidate_id);
}

bool new_citizen(Elections& election) {
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
	return election.add_person(name, id, year, district_id);
}

bool set_citizen_as_candidate(Elections& election) {
	int candidate_id, party_id, district_id;
	cout << "Enter candidate ID: ";
	cin >> candidate_id;
	cout << "Enter district ID: ";
	cin >> district_id;
	cout << "Enter party ID: ";
	cin >> party_id;
	return election.add_person_as_candidate(candidate_id, party_id, district_id);
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
		flag = new_district(election);
		break;
	case 2:
		flag = new_citizen(election);
		break;
	case 3:
		flag = new_party(election);
		break;
	case 4:
		flag = set_citizen_as_candidate(election);
		break;
	case 5:
		election.print_districts();
		break;
	case 6:
		election.print_voters();
		break;
	case 7:
		election.print_parties();
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

void print_statistics(Elections& election) {
	int num_of_districts = election.get_num_districts();
	int num_of_parties = election.get_num_parties();

	for (int i = 1; i <= num_of_districts; i++)
	{
		const District& district = election.get_district(i);
		int winner_party_in_district = district.get_winner_party();
		int winner_candidate_id = election.get_party(winner_party_in_district).get_candidate_id();

		cout << "============================================ " << endl;
		cout << district << " | Winning candidate: " << winner_candidate_id << endl;

		for (int j = 1; j <= num_of_parties; j++)
		{
			const Party& party = election.get_party(j);
			int num_of_candidates_from_party = district.get_party_candidates_num(j);
			const PersonList& candidate_lst = party.get_candidates_list_from_district(i);

			if (candidate_lst.get_person_number() < num_of_candidates_from_party)
			{	//There are not enough candidates from this district 
				cout << "There are not enough candidates from district " << i << endl;
				exit(1);
			}
			cout << "\nParty No." << j << endl;
			candidate_lst.printList(num_of_candidates_from_party);
			cout << "Total votes - " << district.get_party_votes(j) << endl;
			cout << "Percentage of votes - " << district.calc_party_percent_in_votes(j) << endl;
		}
		cout << "\nPercentage of votes in the district: " << district.calc_voters_percentage() << endl << endl;
	}
}

void print_results(Elections& election) {
	int size = 0;
	Party** arr = election.get_sorted_parties_arr(size);

	cout << "\n~ Results ~" << endl;
	for (int i = 0; i < size; i++)
	{
		const Party& party = *arr[i];
		cout << "ID: " << party.get_id() << " Name: " << party.get_name() << endl;
		cout << "First candidate: " << party.get_candidate_id() << endl;
		cout << "Total candidates: " << party.get_total_candidates() << endl;
		cout << "Votes count: " << party.get_total_votes() << endl;
		cout << "---------------------------- " << endl;
	}
	delete[] arr;
}

void finish(Elections& election) {
	election.final_evaluation();
	print_statistics(election);
	print_results(election);
}



