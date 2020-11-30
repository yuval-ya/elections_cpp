#include "Elections.h"


Elections::Elections(int day, int month, int year) : _day(day), _month(month), _year(year) {}

void Elections::add_distric(String name, int number_of_candidates)
{
	// check if there is already district with the same name
    District new_distric(name, number_of_candidates);
    _districs.add(new_distric);
    _parties.add_district_to_party();
}

bool Elections::add_person(String name, int id, int birth_year, int distric_num)
{
    // check if person can vote 
    if (!(_voters.getPersonPtr(id) == nullptr) || distric_num > District::total_districts) {
        return false;
    }
    Person new_person(name, id, birth_year, distric_num);
    PersonPtr person_ptr = _voters.addPerson(new_person);
    _districs.get(distric_num).addPerson(person_ptr);
    return true;
}

void Elections::add_party(String name, int candidate_id)
{
    Party new_party = Party(name,candidate_id);
    _parties.add(new_party);
	_districs.add_party_to_district();
}

bool Elections::add_person_as_candidate(int person_id, int party_id, int district_id)
{
    if (district_id <= District::total_districts)
    {
        PersonPtr candidate = _districs.get(district_id).getPersonPtr(person_id);
        
        if (!(candidate == nullptr) && !candidate->isCandidate() && candidate->getDistrict() == district_id)
        {
            _parties.get(party_id).add_candidate(candidate, district_id);
            candidate->setAsCandidate();
            return true;
        }
    }
    return false;
}

void Elections::print_voters() const
{
    _voters.printList();
}

void Elections::print_districts() const
{
    _districs.print();
}

void Elections::print_parties() const
{
    _parties.print();
}

bool Elections::vote(int person_id, int party_id)
{
	PersonPtr person = _voters.getPersonPtr(person_id);
	if (person == nullptr || person->isVoted() || party_id > Party::total_parties) {
		return false;
	}
	int district_id = person->getDistrict();
	_districs[district_id - 1].vote(party_id);
	person->setVoted();
	return true;
}

void Elections::election_evaluation() {
	int num_of_districts = _districs.get_length();
	int num_of_parties = _parties.get_length();
	
	for (int i = 0; i < num_of_districts; i++) 
	{ 
		int district_id = i + 1;
		int winner_party_in_cur_district = _districs[i].get_winner_party_id();
		_parties[winner_party_in_cur_district - 1].add_total_candidates(_districs[i].get_number_of_candidates());
		int winner_candidate_id = _parties.get(winner_party_in_cur_district).get_candidate_id();
		
		cout << "============================================ " << endl;
		cout << "id" << " | " << "name" << " | " << "number of candidates" << " | " << "winning candidate" << endl;
		cout << _districs[i] << winner_candidate_id << endl;

		for (int j = 0; j < num_of_parties; j++)
		{
			int party_id = j + 1;
			float cur_percent = _districs[i].calc_party_percent_in_votes(party_id);
			int votes_in_district_to_party = _districs[i].get_party_votes(party_id);
			int num_of_candidates_from_party = _districs[i].calc_final_sum_of_candidates_from_party(party_id);
			_parties[j].add_total_votes(votes_in_district_to_party);

			cout << "Party No." << party_id << endl;
			_parties[j].print_final_candidates_for_district(district_id, num_of_candidates_from_party);
			cout << "Total votes - " << votes_in_district_to_party << endl;
			cout << "Percentage of votes - " << cur_percent << endl;
		}
		cout << "Percentage of votes in the district: " << _districs[i].calc_voters_percentage() << endl << endl;
	}
}

void Elections::election_result() {
	int num_of_parties = _parties.get_length();
	//
	// sort partiesArray
	//
	cout << endl;
	for (int i = 0; i < num_of_parties; i++)
	{
		_parties[i].print_election_result();
	}

}
void Elections::finish_election() {
	election_evaluation();
	election_result();
}


