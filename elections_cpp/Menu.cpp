#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::start(Elections& election)
{
    int choice = 1;
    int year, month, day;
    cout << "Enter election's date (year,month,day): "<<endl;
    cin >> year >> month >> day;
    election.setDate(year,month,day);
    
    while (choice != 10) {
        cout << "\nMain menu - choose an option:"<<endl;
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
            cout << "\nOops! Something went wrong\nplease try again"<<endl;
        }
		cin.ignore();
    }
}


bool Menu::new_district(Elections& election) {
    char name[MAX_SIZE];
    int candidates_num;
    cout << "Enter district name: ";
    cin.ignore();
	cin.getline(name, MAX_SIZE);
    cout << "Enter number of candidates: ";
    cin >> candidates_num;
    return election.add_district(name, candidates_num);
}

bool Menu::new_party(Elections& election) {
    char name[MAX_SIZE];
    int candidate_id;
    cout << "Enter party name: ";
    cin.ignore(); 
	cin.getline(name, MAX_SIZE);
    cout << "Enter first candidate ID: ";
    cin >> candidate_id;
    return election.add_party(name, candidate_id);
}

bool Menu::new_citizen(Elections& election) {
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

bool Menu::set_citizen_as_candidate(Elections& election) {
    int candidate_id, party_id, district_id;
    cout << "Enter candidate ID: ";
    cin >> candidate_id;
    cout << "Enter district ID: ";
    cin >> district_id;
    cout << "Enter party ID: ";
    cin >> party_id;
    return election.add_person_as_candidate(candidate_id, party_id, district_id);
}


bool Menu::vote(Elections& election) {
    int id, party_id;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter party ID: ";
    cin >> party_id;
    return election.vote(id, party_id);
}

bool Menu::options(Elections& election, int choice)
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

void Menu::print_statistics(Elections& election) {
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

void Menu::print_results(Elections& election) {
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

void Menu::finish(Elections& election) {
	election.final_evaluation();
	print_statistics(election);
	print_results(election);
}