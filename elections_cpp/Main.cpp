#include "Main.h" 

using namespace elections;
using namespace std;
using namespace mySTL;

int main(void) {
    try {
        mainMenu();
		cout << "Bye!" << endl;
		return 0;
    }
    catch (...)
    {
        cout << "Error: Program exit with return value -1" << endl;
        return -1;
    }
}

void mainMenu()
{
	Elections* electionsRound = nullptr;
	int option;

	cout << endl << "Elections Manager" << endl;
	while (true) {
		cout << "Main Menu - Choose an option:" << endl;
		cout << "1.Create new elections round." << endl;
		cout << "2.Load an existing round of elections." << endl;
		cout << "3.Exit." << endl;

		try {
			cin >> option;
			switch (static_cast<MainMenu>(option)) {
			case MainMenu::NEW:
				electionsRound = createNewRound();
				break;
			case MainMenu::LOAD:
				electionsRound = loadElections();
				break;
			case MainMenu::EXIT:
				return;
				break;
			default:
				throw invalid_argument("Invalid option");
				break;
			}
			break;
		}
		catch (const exception& ex) {
			cout << "Error: " << ex.what() << endl;
			cout << "Please try again" << endl;
		}
	}

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
        catch (const invalid_argument& ex) {
			cout << "Error: " << ex.what() << endl;
			cout << "Please try again" << endl;
        }
    }
    
	while (true) {
		try {
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

			break;
		}
		catch (const invalid_argument& ex) {
			cout << "Error: " << ex.what() << endl;
			cout << "Please try again" << endl;
		}	
	}
    return electionsRound;
}


void start(Elections** election)
{
    int choice;
    do  {
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
            cin.ignore();
            cin >> choice;            
            options(election, static_cast<ElectionsMenu>(choice));
        }
		catch (const char* msg) {
            cout << "Error: " << msg <<endl;
            cout << "Please try again" <<endl;
        }
        catch (const exception& ex) {
            cout << "Error: " << ex.what() <<endl;
            cout << "Please try again" <<endl;
        }
		catch (...) {
			cout << "Error: An unexpected error occurred"<< endl;
			cout << "Please try again" << endl;
		}
 
	} while (choice != static_cast<int>(ElectionsMenu::EXIT));
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
        {
            Elections* tmp = loadElections();
            delete *election;
            *election = tmp;
        }
            break;
        default:
			throw invalid_argument("Wrong input");
            break;
    }
}


void newDistrict(Elections& election) {
    string name;
    int candidates_num, type;
    cout << "Enter district name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter district type: (" ;
    cout << static_cast<int>(DistrictType::DIVIDED) <<" for Divided, ";
    cout << static_cast<int>(DistrictType::UNIFIED) << " for Unified) ";
    cin >> type;
    cout << "Enter number of candidates: ";
    cin >> candidates_num;
    election.addDistrict(name, candidates_num, static_cast<DistrictType>(type));
}

void newParty(Elections& election) {
    string name, candidate_id;
    cout << "Enter party name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter first candidate ID: ";
    cin >> candidate_id;
    election.addParty(name, candidate_id);
}

void newCitizen(Elections& election) {
    string name, id;
    int year, district_id = 1;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
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
    int party_id, district_id = 1;
    string candidate_id;
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
    int party_id;
    string id;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter party ID: ";
    cin >> party_id;
    election.vote(id, party_id);
}

Elections* loadElections()
{
	Elections* electionsRound;
	string name;
	cout << "Enter file name: ";
	cin >> name;
	ifstream infile(name, ios::binary);

	try {
		if (!infile.is_open())
			throw File_Error("Unable to open file");
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

void saveToFile(Elections& election)
{
    string name;
    cout << "Enter file name: ";
    cin >> name;
    
    ofstream outfile(name, ios::binary);
    try {
		if (!outfile.is_open())
			throw File_Error("Unable to open file");
        ElectionsLoader::save(outfile, &election);
    }
    catch (...) {
        if (outfile)
            outfile.close();
		throw;
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
            catch (const runtime_error& ex) {
                cout << "Error: " << ex.what() << endl;
                cout << "The number of voters in this district is 0!" << endl;
            }
        }
        try {
            cout << "\nPercentage of votes in the district: " << district->calcVotersPercentage() << endl << endl;
        }
        catch (const runtime_error& ex) {
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



