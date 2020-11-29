//
//  PersonList.h
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 25/11/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#pragma once
#include <iostream>
#include "PersonPtr.h"

class PersonList {    
public:
    struct Node {
        PersonPtr  person_p;
        Node*      next = nullptr;
    };
    
    PersonList();
    ~PersonList();
    
    Node* getHead() { return _head; }
    Node* getTail() { return _tail; }
    
    PersonPtr addPerson(const Person& p);
    const Person& addPerson(PersonPtr p);
    
    PersonPtr getPersonPtr(int idnum);
    const Person& getPerson(int idnum) const;
        
    void printList();
    bool isEmpty();

private:
    Node* _head;
    Node* _tail;
    int   _person_count;
};
