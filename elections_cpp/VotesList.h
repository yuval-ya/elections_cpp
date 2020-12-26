#pragma once
#include <ostream>
#include "PersonPtr.h"
#include "Party.h"

namespace elections {

class VotesList
{
	// Class to store list of voters and which parties they voted for.

	public:
		// Node to store pointer to a person and party
		struct Node {
			PersonPtr	person_p;
			Party*		party_p;
			Node*		next = nullptr;
		};

		VotesList();
		~VotesList();

		void makeEmpty();

		Node* getHead() { return _head; }
		Node* getTail() { return _tail; }
		
		// Get the id of the party the person voted for
		int getVote(int id) const;

		bool setVote(PersonPtr person, Party* party);

		int getVotesCount() const { return _votesCount; }

		bool isEmpty() const;

		// Recives a pointer to person and party, and inserts it to the end of the list
		bool addVote(PersonPtr person, Party* party);

		const VotesList& operator=(const VotesList& other);

		friend std::ostream& operator<<(std::ostream& os, const VotesList& p_lst);

		bool save(std::ostream& out) const;


	private:
		Node* _head;
		Node* _tail;
		int   _votesCount;

	};

}
