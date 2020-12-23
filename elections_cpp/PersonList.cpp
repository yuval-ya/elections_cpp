//
//  PersonList.cpp
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 25/11/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//
#include "PersonList.h"
#include <iostream>
using namespace std;

namespace elections {

	PersonList::PersonList() : _head(nullptr), _tail(nullptr), _personCount(0) {
	}

	PersonList::~PersonList() {
		Node* curr = _head;
		Node* temp;

		while (curr != nullptr) {
			temp = curr;
			curr = curr->next;
			delete temp;
		}
	}


    void PersonList::print(int count) const
    {
        Node* curr = _head;
            
        for (int i = 0; (i < count || count == -1) && curr != nullptr; i++)
        {
            cout << *(curr->person_p) << endl;
            curr = curr->next;
        }
    }


	PersonPtr PersonList::addPerson(const Person& p)
	{
		PersonPtr person_p = new Person(p);

		Node* newnode = new Node();
		newnode->person_p = person_p;

		if (_head == nullptr) {
			_head = _tail = newnode;
		}
		else
		{
			_tail->next = newnode;
			_tail = _tail->next;
		}

		_personCount++;
		return person_p;
	}


	const Person& PersonList::addPerson(PersonPtr p) {
		Node* newnode = new Node();
		newnode->person_p = p;


		if (_head == nullptr) {
			_head = _tail = newnode;
		}
		else
		{
			_tail->next = newnode;
			_tail = _tail->next;
		}
		_personCount++;
		return *p;
	}


	bool PersonList::isEmpty() const {
		return _head == nullptr;
	}


	PersonPtr PersonList::getPersonPtr(int idnum) {
		Node* curr = _head;
		PersonPtr res = nullptr;

		while (curr != nullptr && curr->person_p->getID() != idnum) {
			curr = curr->next;
		}
		if (curr != nullptr) {
			res = curr->person_p;
		}

		return res;
	}


	const Person& PersonList::getPerson(int idnum) const {
		Node* curr = _head;
		PersonPtr res = nullptr;

		if (curr != nullptr)
		{
			while (curr->person_p->getID() != idnum) {
				curr = curr->next;
			}
			if (curr != nullptr) {
				res = curr->person_p;
			}
		}

		return *res;
	}


const PersonList& PersonList::operator=(const PersonList& other)
{
    if (&other != this){
        Node* curr = _head;
        Node* temp;

        while (curr != nullptr) {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
        
        curr = other._head;
        while(curr != nullptr){
            this->addPerson(curr->person_p);
            curr = curr->next;
        }
    }
    
    return *this;
}
	ostream& operator<<(ostream& os, const PersonList& p_lst) {
		PersonList::Node* curr = p_lst._head;

		while (curr != nullptr) {
			os << *(curr->person_p) << endl;
			curr = curr->next;
		}
		return os;
	}

}
