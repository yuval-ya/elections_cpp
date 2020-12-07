#include "Elections.h"
#include <cstdlib>

Elections::Elections(int day, int month, int year) : _day(day), _month(month), _year(year) {}

void Elections::setDate(int year, int month, int day) {
	_year = year;
	_month = month;
	_day = day;
}

bool Elections::add_district(String name, int number_of_candidates)
{
    District new_distric(name, number_of_candidates);
    _districts.add(new_distric);
    _parties.add_district_to_party();
	return true;
}

bool Elections::add_person(String name, int id, int birth_year, int distric_num)
{
    if (_voters.getPersonPtr(id) != nullptr || distric_num > District::total_districts) {
        return false;
    }
    Person new_person(name, id, birth_year, distric_num);
    PersonPtr person_ptr = _voters.addPerson(new_person);
    _districts.get(distric_num).addPerson(person_ptr);
    return true;
}

bool Elections::add_party(String name, int candidate_id)
{
	PersonPtr candidate = _voters.getPersonPtr(candidate_id);
	if (candidate == nullptr) {  // more conditions? *******************************************************************
		return false;
	}
    Party new_party = Party(name,candidate_id);
    _parties.add(new_party);
	_districts.add_party_to_district();
	candidate->setAsCandidate(); // can the first candidate can be a regular candidate? ********************************
	return true;
}

bool Elections::add_person_as_candidate(int person_id, int party_id, int district_id)
{
    if (district_id <= _districts.get_length() && party_id <= _parties.get_length())
    {
        PersonPtr candidate = _districts.get(district_id).getPersonPtr(person_id);

        if (candidate != nullptr && !candidate->isCandidate() && candidate->getDistrict() == district_id)
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
    _districts.print();
}

void Elections::print_parties() const
{
    _parties.print();
}

bool Elections::vote(int person_id, int party_id)
{
	PersonPtr person = _voters.getPersonPtr(person_id);
	if (person == nullptr || person->isVoted() || party_id > _parties.get_length()) {
		return false;
	}
	int district_id = person->getDistrict();
	_districts[district_id - 1].vote(party_id);
	_parties[party_id - 1].add_total_votes(1);
	person->setVoted();
	return true;
}

void Elections::final_evaluation() {
	int num_of_districts = _districts.get_length();
    int num_of_parties = _parties.get_length();
    
    for (int i = 0; i < num_of_parties; i++)
    {
        _parties[i].set_total_candidates(0);
    }
    
	for (int i = 0; i < num_of_districts; i++)
	{
		int winning_party_in_district = _districts[i].eval_partition();
		
		// The winning party gets the number of candidates in the current district
		_parties[winning_party_in_district - 1].add_total_candidates(_districts[i].get_number_of_candidates());
	}
}



Party** Elections::get_sorted_parties_arr(int& size) {
	int num_of_parties = _parties.get_length();
	Party** res = new Party*[num_of_parties];

	for (int i = 0; i < num_of_parties; i++)
	{
		res[i] = &_parties[i];
	}
    Party::mergeSort(res, 0, num_of_parties - 1);
    // qsort(res, num_of_parties, sizeof(Party*), Party::compare_parties);   ***********************************
	size = num_of_parties;
	return res;
}

