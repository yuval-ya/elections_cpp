#include "Menu.h"


void Menu::start()
{
    int choice = 1;
    int year, month, day;
    cout << "Enter election's date (year,month,day): "<<endl;
    cin >> year >> month >> day;
    _election.setDate(year,month,day);
    
    while (choice != 10) {
        cout << "Main menu - choose an option:"<<endl;
        cout << "1.Add District." << endl;
        cout << "2.Add Citizen." << endl;
        cout << "3.Add Party." << endl;
        cout << "4.Add Person as a Party Member." << endl;
        cout << "5.Print all Districts." << endl;
        cout << "6.Print all Citizens." << endl;
        cout << "7.Print all Parties." << endl;
        cout << "8.Vote." << endl;
        cout << "9.Show Election result." << endl;
        cout << "10.Exit." << endl;
        cin >> choice;
        if (!options(choice)) {
            cout << "Oops! Something went wrong\nplease try again"<<endl;
        }
    }
}



///   Change core functions to return bool ////// 
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
        case 3:
            flag = new_party();
        case 4:
            flag = set_citizen_as_candidate();
        case 5:
            _election.print_districts();
        case 6:
            _election.print_voters();
        case 7:
            _election.print_parties();
        case 8:
            flag = vote();
        case 9:
            // eva;
        default:
            flag = false;
            break;
    }
    return flag;
}


