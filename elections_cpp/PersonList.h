//
//  PersonList.h
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 25/11/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#pragma once
#include <iostream>
#include "Person.h"

class PersonList {
    
public:
    struct Node {
        Person*    person_p;
        Node*      next = nullptr;
    };
    
    PersonList();
    ~PersonList();
    
    Node* getHead() { return _head; }
    Node* getTail() { return _tail; }
    bool addPerson(const Person& p);
    bool addPerson(Person* p);

    bool isEmpty();
    Person& getPerson(int idnum);
    void printList();
    
private:
    Node* _head;
    Node* _tail;
    int   _person_count;
    
};
