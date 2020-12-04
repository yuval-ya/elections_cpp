#include "Menu.h"

Menu::Menu(Elections& e) : _election(e)
{
}

Menu::~Menu()
{
}

void Menu::start()
{
    int choice = 1;
    int year, month, day;
    cout << "Enter election's date (year,month,day): "<<endl;
    cin >> year >> month >> day;
    _election.setDate(year,month,day);
    
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
        if (!options(choice)) {
            cout << "\nOops! Something went wrong\nplease try again"<<endl;
        }
		cin.ignore();
    }
}


bool Menu::new_district() {
    char name[MAX_SIZE];
    int candidates_num;
    cout << "Enter district name: ";
    cin >> name;
    cout << "Enter number of candidates: ";
    cin >> candidates_num;
    return _election.add_distric(name, candidates_num);
}

bool Menu::new_party() {
    char name[MAX_SIZE];
    int candidate_id;
    cout << "Enter party name: ";
    cin >> name;
    cout << "Enter first candidate ID: ";
    cin >> candidate_id;
    return _election.add_party(name, candidate_id);
}

bool Menu::new_citizen() {
    char name[MAX_SIZE];
    int id, year, district_id;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter id: ";
    cin >> id;
    cout << "Enter year of birth: ";
    cin >> year;
    cout << "Enter district id: ";
    cin >> district_id;
    return _election.add_person(name, id, year, district_id);
}

bool Menu::set_citizen_as_candidate() {
    int candidate_id, party_id, district_id;
    cout << "Enter candidate ID: ";
    cin >> candidate_id;
    cout << "Enter district ID: ";
    cin >> district_id;
    cout << "Enter party ID: ";
    cin >> party_id;
    return _election.add_person_as_candidate(candidate_id, party_id, district_id);
}


bool Menu::vote() {
    int id, party_id;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter party ID: ";
    cin >> party_id;
    return _election.vote(id, party_id);
}

bool Menu::options(int choice)
{
    bool flag = true;
    switch (choice) {
        case 1:
            flag = new_district();
            break;
        case 2:
            flag = new_citizen();
			break;
        case 3:
            flag = new_party();
			break;
        case 4:
            flag = set_citizen_as_candidate();
			break;
        case 5:
            _election.print_districts();
			break;
        case 6:
            _election.print_voters();
			break;
        case 7:
            _election.print_parties();
			break;
        case 8:
            flag = vote();
			break;
        case 9:
			finish();
			break;
		case 10:
			break;
        default:
            flag = false;
            break;
    }
    return flag;
}

void Menu::print_statistics() {
	int num_of_districts = _election.get_num_districts();
	int num_of_parties = _election.get_num_parties();

	for (int i = 1; i <= num_of_districts; i++) 
	{ 
		const District& district = _election.get_district(i);
		int winner_party_in_cur_district = district.get_winner_party_id();
		int winner_candidate_id = _election.get_party(winner_party_in_cur_district).get_candidate_id();
			
		cout << "============================================ " << endl;
		cout << "ID" << " | " << "Name" << " | " << "Number of candidates" << " | " << "Winning candidate" << endl;
		cout << district << winner_candidate_id << endl;
	
		for (int j = 1; j <= num_of_parties; j++)
		{
			const Party& party = _election.get_party(j);
			int num_of_candidates_from_party = district.calc_final_sum_of_candidates_from_party(j);
			const PersonList& candidate_lst = party.get_candidates_list_from_district(i);
				
			if (candidate_lst.get_person_number() < num_of_candidates_from_party){
				exit(1); //There are not enough candidates from this district 
			}
			cout << "Party No." << j << endl;
			candidate_lst.printList(num_of_candidates_from_party);
			cout << "Total votes - " << district.get_party_votes(j) << endl;
			cout << "Percentage of votes - " << district.calc_party_percent_in_votes(j) << endl;
		}
		cout << "Percentage of votes in the district: " << district.calc_voters_percentage() << endl << endl;
	}
}

void Menu::print_results() {
	int num_of_parties = _election.get_num_parties();
	
	cout << "\n~ Results ~" << endl;
	for (int i = 1; i <= num_of_parties; i++)
	{
		const Party& party = _election.get_party(i);
		cout << "ID: " << party.get_id() << " Name: " << party.get_name() << endl;
		cout << "First candidate: " << party.get_candidate_id() << endl;
		cout << "Total candidates: " << party.get_total_candidates() << endl;
		cout << "Votes count: " << party.get_total_votes() << endl;
		cout << "---------------------------- " << endl;	
	}
}

void Menu::finish() {
	_election.final_evaluation();
	print_statistics();
	_election.sort_parties();
	print_results();
}