//
//  PersonList.h
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 25/11/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#pragma once
#include <ostream>
#include "PersonPtr.h"

namespace elections {

class PersonList {
    
    // Class to store list of Person
    
public:
    
    // Node to store pointer to a person and the next node in the list
    struct Node {
        PersonPtr  person_p;
        Node*      next = nullptr;
    };
    
    PersonList();
    ~PersonList();

	void makeEmpty();

    Node* getHead() { return _head; }
    Node* getTail() { return _tail; }
    PersonPtr getPersonPtr(int idnum);
    const Person& getPerson(int idnum) const;
    int getPersonNumber() const { return _personCount; }
   
	void print(int count = -1) const;
    bool isEmpty() const;
    
	
    //// Recives a refernce the a person, allocates new node and person pointer, and inserts it to the end of the list
    //PersonPtr addPerson(const Person& p);

    // Recives a pointer to person, and inserts it to the end of the list
    const Person& addPerson(PersonPtr p);

    const PersonList& operator=(const PersonList& other);

	friend std::ostream& operator<<(std::ostream& os, const PersonList& p_lst);

	//bool load(std::istream& in);     // delete ????
	bool save(std::ostream& out) const;
    
private:
    Node* _head;
    Node* _tail;
    int   _personCount;
};

}
