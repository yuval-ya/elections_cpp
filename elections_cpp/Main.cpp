#define _CRTDB_MAP_ALLOC
//#include <crtdbg.h>

#include "Main.h" 
#include "Utilities.h"

using namespace elections;
using namespace std;
using namespace mySTL;

int main(void) {
    
    try {
        mainMenu();
    }
    catch (exception& ex)
    {
        cout << "Error: " << ex.what() << endl;
        cout << "Program exit with return value -1" << endl;

        return -1;
    }
    
    cout << "Bye!" << endl;
    //	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //	_CrtDumpMemoryLeaks();
    return 0;
}


void mainMenu()
{
    Elections* electionsRound = nullptr;
    int option;
    bool flag = true;
    
    while (flag) {
        cout << endl << "Elections Manager -" << endl;
        cout << endl << "Choose an option:" << endl;
        cout << "1.Create new elections round." << endl;
        cout << "2.Load an existing round of elections." << endl;
        cout << "3.Exit." << endl;
        cin >> option;
        
        try {
            switch (static_cast<MainMenu>(option)) {
                case MainMenu::NEW:
                    electionsRound = createNewRound();
                    break;
                case MainMenu::LOAD:
                    electionsRound = loadElections();
                    break;
                case MainMenu::EXIT:
                    flag = false;
                    break;
                default:
                    throw invalid_argument("Invalid option");
                    break;
            }
            flag = false;
        }
        catch (invalid_argument& ex) {
            cout << "Error: " << ex.what() << endl;
        }
    }
    
    if (electionsRound) {
        //Menu::test(*electionsRound);
        try {
            start(&electionsRound);
            delete electionsRound;
        }
        catch (...) {
            if (electionsRound)
                delete electionsRound;
            throw;
        }
    }
}

Elections* createNewRound() 
{
    Elections* electionsRound = nullptr;
    Date date;
    
    while (true) {
        cout << "Enter the date of the elections (day-month-year): ";
        try {
            cin >> date;
            break;
        }
        catch (invalid_argument& ex) {
            cout << "Error: " << ex.what() << endl;
        }
    }
    
    int roundType;
    cout << "Choose the type of the elections (";
    cout << static_cast<int>(ElectionsType::RERGULAR) << " for Regular , ";
    cout << static_cast<int>(ElectionsType::SIMPLE) << " for Simple): ";
    cin >> roundType;
    
    switch (static_cast<ElectionsType>(roundType))
    {
        case ElectionsType::RERGULAR:
        {
            electionsRound = new Elections(date);
        }
            break;
        case ElectionsType::SIMPLE:
        {
            int numOfCandidates;
            cout << "Enter the number of candidates that will be in the election: ";
            cin >> numOfCandidates;
            electionsRound = new SimpleElections(numOfCandidates, date);
        }
            break;
        default:
            throw invalid_argument("Invalid elections type");
            break;
    }
    return electionsRound;
    
}

Elections* loadElections()
{
    Elections* electionsRound;
    char name[MAX_SIZE];
    cout << "Enter file name: ";
    cin >> name;
    ifstream infile;
    infile.exceptions(ifstream::eofbit);
    
    try {
        infile.open(name, ios::binary);
        electionsRound = ElectionsLoader::load(infile);
        infile.close();
    }
    catch (...) {
        if (infile)
            infile.close();
        throw;
    }
    
    return electionsRound;
}


void start(Elections** election)
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
        
        try {
            cin >> choice;
            if(choice < 1 || choice > 12)
                throw "Wrong input";
            
            options(election, static_cast<ElectionsMenu>(choice));
        }
        catch (invalid_argument& ex) {
            cout << "Error: " << ex.what() <<endl;
            cout << "Please try again" <<endl;
        }
        catch (char* msg) {
            cout << "Error: " << msg <<endl;
            cout << "Please try again" <<endl;
        }
        
        cin.ignore();
    }
}


void options(Elections** election, ElectionsMenu choice)
{
    Elections& e = **election;
    switch (choice) {
        case ElectionsMenu::ADD_DISTRICT:
            if (typeid(e) == typeid(SimpleElections))
                throw "Can't add district to simple elections.";
            newDistrict(e);
            break;
        case ElectionsMenu::ADD_CITIZEN:
            newCitizen(e);
            break;
        case ElectionsMenu::ADD_PARTY:
            newParty(e);
            break;
        case ElectionsMenu::ADD_CANDIDATE:
            setCitizenAsCandidate(e);
            break;
        case ElectionsMenu::PRINT_DISTRICTS:
            if (typeid(e) == typeid(SimpleElections))
                throw "There are no districts in simple elections.";
            print(e.getDistricts());
            break;
        case ElectionsMenu::PRINT_CITIZENS:
            print(e.getVoters());
            break;
        case ElectionsMenu::PRINT_PARTIES:
            print(e.getParties());
            break;
        case ElectionsMenu::VOTE:
            vote(e);
            break;
        case ElectionsMenu::RESULTS:
            finish(e);
            break;
        case ElectionsMenu::EXIT:
            break;
        case ElectionsMenu::SAVE:
            saveToFile(e);
            break;
        case ElectionsMenu::LOAD:
            delete *election;
            *election = loadElections();
            break;
        default:
            break;
    }
}


void newDistrict(Elections& election) {
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
    election.addDistrict(name, candidates_num, static_cast<DistrictType>(type));
}

void newParty(Elections& election) {
    char name[MAX_SIZE];
    int candidate_id;
    cout << "Enter party name: ";
    cin.ignore();
    cin.getline(name, MAX_SIZE);
    cout << "Enter first candidate ID: ";
    cin >> candidate_id;
    election.addParty(name, candidate_id);
}

void newCitizen(Elections& election) {
    char name[MAX_SIZE];
    int id, year, district_id = 1;
    cout << "Enter name: ";
    cin.ignore();
    cin.getline(name, MAX_SIZE);
    cout << "Enter id: ";
    cin >> id;
    cout << "Enter year of birth: ";
    cin >> year;
    if (typeid(election) != typeid(SimpleElections)) {
        cout << "Enter district id: ";
        cin >> district_id;
    }
    election.addPerson(name, id, year, district_id);
}

void setCitizenAsCandidate(Elections& election) {
    int candidate_id, party_id, district_id = 1;
    cout << "Enter candidate ID: ";
    cin >> candidate_id;
    if (typeid(election) != typeid(SimpleElections)) {
        cout << "Enter district id: ";
        cin >> district_id;
    }
    cout << "Enter party ID: ";
    cin >> party_id;
    election.addPersonAsCandidate(candidate_id, party_id, district_id);
}

void vote(Elections& election) {
    int id, party_id;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter party ID: ";
    cin >> party_id;
    election.vote(id, party_id);
}


void saveToFile(Elections& election)
{
    char name[MAX_SIZE];
    cout << "Enter file name: ";
    cin >> name;
    
    ofstream outfile;
    outfile.exceptions(ostream::eofbit); // No need to check this bit
    
    try {
        outfile.open(name, ios::binary);
        ElectionsLoader::save(outfile, &election);
    }
    catch (ostream::failure& ex) {
        if (outfile)
            outfile.close();
        throw "opening/writing file failed";
    }
}

void printStatistics(Elections& election) {
    cout << endl << "Elections Date: " << election.getDate() << endl << endl;
    int i = 0;
    for (auto district : election.getDistricts())
    {
        if (typeid(election) != typeid(SimpleElections)) {
            cout << "------------------- District No." << (++i) << " -------------------" << endl;
            cout << *district << endl;
        }
        cout << "Winning candidates: " << endl;
        district->showWinners(cout);
        for (auto party : election.getParties()) {
            int numOfCandidatesFromParty = district->getPartyCandidatesNum(party->getId());
            const List<PersonPtr>& candidateList = party->getCandidateList(district->getId());
            cout << "\nParty ID " << party->getId() << endl;
            
            auto iter = candidateList.begin();
            for (int j = 0; iter != candidateList.end() && j < numOfCandidatesFromParty; ++iter, ++j)
                cout << *iter << endl;
            
            if (candidateList.size() < numOfCandidatesFromParty)
                cout << "Error: There are not enough candidates in the party" << endl;
            
            cout << "Total votes - " << district->getPartyVotes(party->getId()) << endl;
            try {
                cout << "Percentage of votes - " << district->calcPartyPercentInVotes(party->getId()) << endl;
            }
            catch (runtime_error& ex) {
                cout << "Error: " << ex.what() << endl;
                cout << "The number of voters in this district is 0!" << endl;
            }
        }
        try {
            cout << "\nPercentage of votes in the district: " << district->calcVotersPercentage() << endl << endl;
        }
        catch (runtime_error& ex) {
            cout << "Error: " << ex.what() << endl;
            cout << "The number of citizens in this district is 0!" << endl;
        }
    }
}

void printResults(Elections& election) {
    cout << "\n~ Results ~" << endl;
    for (auto party : election.getParties()){
        cout << "ID: " << party->getId() << " Name: " << party->getName() << endl;
        cout << "First candidate: " << party->getCandidate().getID() << endl;
        cout << "Total candidates: " << party->getTotalCandidates() << endl;
        cout << "Votes count: " << party->getTotalVotes() << endl;
        cout << "---------------------------- " << endl;
    }
}

void finish(Elections& election) {
    election.finalEvaluation();
    printStatistics(election);
    election.sortPartiesArray();
    printResults(election);
}



