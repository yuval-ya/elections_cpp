#define _CRTDB_MAP_ALLOC
//#include <crtdbg.h>

#include "Main.h" 
#include "Elections.h"
#include "ElectionsLoader.h"
#include "SimpleElections.h"
#include "Menu.h"
#include <fstream>

using namespace elections;
using namespace std;

int main(void) {    

	
	// ifstream infile;
	// infile.open("test", ios::binary);
    // Elections* e = new Elections(infile);
	// infile.close();
    // start(*e);
    // delete e;


    int option;
    cout << endl << "Elections Manager -" << endl;
    cout << endl << "Choose an option:" << endl;
    cout << "1.Create new elections round." << endl;
    cout << "2.Load an existing round of elections." << endl;
    cout << "3.Exit." << endl;
    cin >> option;
    
    switch (static_cast<MainMenu>(option)) {
        case MainMenu::NEW:
        {
            int roundType;
            Date date;
            
            cout << "Choose the type of the elections (" ;
            cout << static_cast<int>(ElectionsType::RERGULAR) << " for Regular , ";
            cout << static_cast<int>(ElectionsType::SIMPLE) <<" for Simple): ";
            cin >> roundType;
            cout << "Enter the date of the elections (day-month-year): ";
            cin >> date;
            
            switch (static_cast<ElectionsType>(roundType))
            {
                case ElectionsType::RERGULAR:
                {
                    Elections election(date);
                    Menu::test(election);
                    start(election);
                }
                    break;
                case ElectionsType::SIMPLE:
                {
                    int numOfCandidates;
                    cout << "Enter the number of candidates that will be in the election: ";
                    cin >> numOfCandidates;
                    SimpleElections election(numOfCandidates, date);
                    Menu::test(election);
                    start(election);
                }
                    break;
                default:
                    cout << "Wrong Input!" << endl;
                    break;
            }
            
        }
            break;
        case MainMenu::LOAD:
        {
            char name[MAX_SIZE];
            cout << "Enter file name: ";
            cin >> name;
            // load
        }
            break;
        case MainMenu::EXIT:
            break;
        default:
            cout << "Wrong Input!" << endl;
            break;
    }
    cout << "Bye!" << endl;
    
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtDumpMemoryLeaks();
    return 0;
}


void start(Elections& election)
{

	// ofstream outfile;
	// outfile.open("test", ios::binary);
	// election.save(outfile);
    // outfile.close();


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
		if(choice < 1 || choice > 12)
			cout << endl << "Wrong input" << endl << "please try again" << endl;
        else if (!options(election, static_cast<EelectionsMenu>(choice))) {
            cout << endl << "Oops! Something went wrong" << endl << "please try again" << endl;
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
    cout << "Enter district type: (" ;
    cout << static_cast<int>(DistrictType::DIVIDED) <<" for Divided, ";
    cout << static_cast<int>(DistrictType::UNIFIED) << " for Unified) ";
    cin >> type;
    cout << "\nEnter number of candidates: ";
    cin >> candidates_num;
    return election.addDistrict(name, candidates_num, static_cast<DistrictType>(type));
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

bool options(Elections& election, EelectionsMenu choice)
{
    bool flag = true;
    switch (choice) {
        case EelectionsMenu::ADD_DISTRICT:
            flag = newDistrict(election);
            break;
        case EelectionsMenu::ADD_CITIZEN:
            flag = newCitizen(election);
            break;
        case EelectionsMenu::ADD_PARTY:
            flag = newParty(election);
            break;
        case EelectionsMenu::ADD_CANDIDATE:
            flag = setCitizenAsCandidate(election);
            break;
        case EelectionsMenu::PRINT_DISTRICTS:
            election.getDistricts().print();
            break;
        case EelectionsMenu::PRINT_CITIZENS:
            election.getVoters().print();
            break;
        case EelectionsMenu::PRINT_PARTIES:
            election.getParties().print();
            break;
        case EelectionsMenu::VOTE:
            flag = vote(election);
            break;
        case EelectionsMenu::RESULTS:
            finish(election);
            break;
        case EelectionsMenu::EXIT:
            break;
        case EelectionsMenu::SAVE:
            break;
        case EelectionsMenu::LOAD:
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
    
    for (int i = 0; i < numOfDistricts; i++)
    {
        const District& district = election.getDistricts()[i];
        
        cout << "------------------- District No." << (i+1) << " -------------------" << endl;
        cout << district << endl << "Winning candidates: "<< endl;
        district.showWinners(cout);
        
        for (int j = 0; j < numOfParties; j++)
        {
            const Party& party = election.getParties()[j];
            int numOfCandidatesFromParty = district.getPartyCandidatesNum(party.getId());
            const PersonList& candidateList = party.getCandidatesArray().get(district.getId());
            
            cout << "\nParty ID " << party.getId() << endl;
            if (candidateList.getPersonNumber() < numOfCandidatesFromParty)
            {	//There are not enough candidates from this district
                cout << "*** There are not enough candidates in the party to district" << i << " ***" << endl;
            }
            candidateList.print(numOfCandidatesFromParty);
            cout << "Total votes - " << district.getPartyVotes(party.getId()) << endl;
            cout << "Percentage of votes - " << district.calcPartyPercentInVotes(party.getId()) << endl;
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



