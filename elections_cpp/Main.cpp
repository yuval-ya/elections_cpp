#define _CRTDB_MAP_ALLOC
#include <crtdbg.h>

#include "Main.h" 
#include "Ut"
#include <list>



using namespace elections;
using namespace std;
using namespace mySTL;

int main(void) {
	{
		//List<int> lst;
		//lst.push_back(1);
		//lst.push_back(3);
		//cout << endl;
		//for (auto num : lst) {
		//	cout << num << " ";
		//}

		mainMenu();
		cout << "Bye!" << endl;
	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
    return 0;
}


void mainMenu()
{
	Elections* electionsRound = nullptr;

	int option;
	cout << endl << "Elections Manager -" << endl;
	cout << endl << "Choose an option:" << endl;
	cout << "1.Create new elections round." << endl;
	cout << "2.Load an existing round of elections." << endl;
	cout << "3.Exit." << endl;
	cin >> option;

	switch (static_cast<MainMenu>(option)) {
	case MainMenu::NEW:
		electionsRound = createNewRound();
		break;
	case MainMenu::LOAD:
		electionsRound = loadElections();
		break;
	case MainMenu::EXIT:
		break;
	default:
		cout << "Wrong Input!" << endl;
		break;
	}

	if (electionsRound) {
		Menu::test(*electionsRound);
		start(&electionsRound);
		delete electionsRound;
	}
}

Elections* createNewRound() 
{
	Elections* electionsRound = nullptr;
	int roundType;
	Date date;

	cout << "Choose the type of the elections (";
	cout << static_cast<int>(ElectionsType::RERGULAR) << " for Regular , ";
	cout << static_cast<int>(ElectionsType::SIMPLE) << " for Simple): ";
	cin >> roundType;
	cout << "Enter the date of the elections (day-month-year): ";
	cin >> date;

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
		cout << "Wrong Input!" << endl;
		break;
	}
	return electionsRound;

}

Elections* loadElections()
{
	char name[MAX_SIZE];
	cout << "Enter file name: ";
	cin >> name;
	ifstream infile;
	infile.open(name, ios::binary);
	if (!infile) {
		cout << "An error occurred while opening the file" << endl;
		exit(-1);
	}
	Elections* electionsRound = ElectionsLoader::load(infile);
	infile.close();
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
        
        cin >> choice;
		if(choice < 1 || choice > 12)
			cout << endl << "Wrong input" << endl << "please try again" << endl;
        else if (!options(election, static_cast<ElectionsMenu>(choice))) {
            cout << endl << "Oops! Something went wrong" << endl << "please try again" << endl;
        }
        cin.ignore();
    }
}


bool options(Elections** election, ElectionsMenu choice)
{
	Elections& e = **election;
	bool flag = true;
	switch (choice) {
	case ElectionsMenu::ADD_DISTRICT:
		if (typeid(e) == typeid(SimpleElections))
			cout << "Can't add district to simple elections." << endl;
		else
			flag = newDistrict(e);
		break;
	case ElectionsMenu::ADD_CITIZEN:
		flag = newCitizen(e);
		break;
	case ElectionsMenu::ADD_PARTY:
		flag = newParty(e);
		break;
	case ElectionsMenu::ADD_CANDIDATE:
		flag = setCitizenAsCandidate(e);
		break;
	case ElectionsMenu::PRINT_DISTRICTS:
		if (typeid(e) == typeid(SimpleElections))
			cout << "There are no districts in simple elections." << endl;
		else
			e.getDistricts().print();
		break;
	case ElectionsMenu::PRINT_CITIZENS:
		print(e.getVoters().begin(), e.getVoters().end());
		//e.getVoters().print();
		break;
	case ElectionsMenu::PRINT_PARTIES:
		e.getParties().print();
		break;
	case ElectionsMenu::VOTE:
		flag = vote(e);
		break;
	case ElectionsMenu::RESULTS:
		finish(e);
		break;
	case ElectionsMenu::EXIT:
		break;
	case ElectionsMenu::SAVE:
		flag = saveToFile(e);
		break;
	case ElectionsMenu::LOAD:
		delete *election;
		*election = loadElections();
		break;
	default:
		flag = false;
		break;
	}
	return flag;
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
    return election.addPerson(name, id, year, district_id);
}

bool setCitizenAsCandidate(Elections& election) {
	int candidate_id, party_id, district_id = 1;
    cout << "Enter candidate ID: ";
    cin >> candidate_id;
	if (typeid(election) != typeid(SimpleElections)) {
		cout << "Enter district id: ";
		cin >> district_id;
	}
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


bool saveToFile(Elections& election)
{
	char name[MAX_SIZE];
	cout << "Enter file name: ";
	cin >> name;

	ofstream outfile;
	outfile.open(name, ios::binary);

	if (!outfile) {
		cout << "An error occurred while opening the file" << endl;
		exit(-1);
	}

	ElectionsLoader::save(outfile, &election);
	outfile.close();
	return true;
}
void printStatistics(Elections& election) {
    int numOfDistricts = election.getDistricts().getLength();
    int numOfParties = election.getParties().getLength();
    
    cout << endl << "Elections Date: " << election.getDate() << endl << endl;
    
    for (int i = 0; i < numOfDistricts; i++)
    {
        const District& district = election.getDistricts()[i];
        
		if (typeid(election) != typeid(SimpleElections)) {
			cout << "------------------- District No." << (i + 1) << " -------------------" << endl;
			cout << district << endl;
		}
		cout << "Winning candidates: " << endl;
        district.showWinners(cout);
        
        for (int j = 0; j < numOfParties; j++)
        {
            const Party& party = election.getParties()[j];
            int numOfCandidatesFromParty = district.getPartyCandidatesNum(party.getId());
            const List<PersonPtr>& candidateList = party.getCandidateList(district.getId());
            
            cout << "\nParty ID " << party.getId() << endl;
            if (candidateList.size() < numOfCandidatesFromParty)
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



