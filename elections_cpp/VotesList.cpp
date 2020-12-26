#include "VotesList.h"

#include <iostream>
using namespace std;



namespace elections {

	VotesList::VotesList() :_head(nullptr), _tail(nullptr), _votesCount(0) {

	}
	VotesList::~VotesList() {
		makeEmpty();
	}

	void VotesList::makeEmpty() {
		Node* curr = _head;
		Node* temp;

		while (curr != nullptr) {
			temp = curr;
			curr = curr->next;
			delete temp;
		}
		_votesCount = 0;
	}


	int VotesList::getVote(int id) const {
		Node* curr = _head;
		int res = -1;

		while (curr != nullptr && curr->person_p->getID() != id) {
			curr = curr->next;
		}
		if (curr != nullptr) {
			res = curr->party_p->getId();
		}
		return res;
	}

	bool VotesList::setVote(PersonPtr person, Party* party) {
		Node* curr = _head;

		while (curr != nullptr && !(curr->person_p == person)) {
			curr = curr->next;
		}
		if (curr != nullptr) {
			curr->party_p = party;
			return true;
		}
		return false;
	}


	bool VotesList::isEmpty() const {
		return _head == nullptr;
	}


	bool VotesList::addVote(PersonPtr person, Party* party) {
		Node* newnode = new Node();
		newnode->person_p = person;
		newnode->party_p = party;

		if (_head == nullptr) {
			_head = _tail = newnode;
		}
		else
		{
			_tail->next = newnode;
			_tail = _tail->next;
		}
		_votesCount++;
		return true;
	}

	ostream& operator<<(ostream& os, const VotesList& v_lst) {

		VotesList::Node* curr = v_lst._head;
		while (curr != nullptr) {
			os << "(Person ID: " << curr->person_p->getID() << ", Party ID: " << curr->party_p->getId() << ")" << endl;
			curr = curr->next;
		}
		return os;
	}

	bool VotesList::save(ostream& out) const {
		out.write(rcastcc(&_votesCount), sizeof(_votesCount));

		Node* curr = _head;
		for (int i = 0; i < _votesCount && curr != nullptr; i++, curr = curr->next)
		{
			int personID = curr->person_p->getID();
			int partyID = curr->party_p->getId();

			out.write(rcastcc(&personID), sizeof(personID));
			out.write(rcastcc(&partyID), sizeof(partyID));
		}
		return true;

	}


	const VotesList& VotesList::operator=(const VotesList& other)
	{
		if (&other != this) {
			Node* curr = _head;
			Node* temp;

			while (curr != nullptr) {
				temp = curr;
				curr = curr->next;
				delete temp;
			}
			curr = other._head;
			while (curr != nullptr) {
				this->addVote(curr->person_p, curr->party_p);
				curr = curr->next;
			}
		}
		return *this;
	}

}
