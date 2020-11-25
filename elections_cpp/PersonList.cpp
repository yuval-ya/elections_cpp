//
//  PersonList.cpp
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 25/11/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#include "PersonList.h"

PersonList::PersonList() : _head(nullptr), _tail(nullptr), _person_count(0) {}

PersonList::~PersonList(){
    Node* curr = _head;
    Node* temp;
    
    while(curr != nullptr){
        temp = curr;
        curr = curr->next;
        if (!temp->person_p->isCandidate())
        {
            delete temp->person_p;
        }
        delete temp;
    }
}

bool PersonList::addPerson(const Person& p)
{
    Person* person_p =  new Person(p);
        
    Node* newnode = new Node();
    newnode->person_p = person_p;
    
    if (_head == nullptr){
        _head = _tail = newnode;
    }
    else
    {
        _tail->next = newnode;
        _tail = _tail->next;
    }
    
    _person_count++;
    return true;
}

bool PersonList::addPerson(Person* p){
        
    Node* newnode = new Node();
    newnode->person_p = p;
    
    if (_head == nullptr){
        _head = _tail = newnode;
    }
    else
    {
        _tail->next = newnode;
        _tail = _tail->next;
    }
    _person_count++;
    return true;
}


bool PersonList::isEmpty(){
    return _head == nullptr;
}

Person& PersonList::getPerson(int idnum) {
    Node* curr = _head;
    Person* res = nullptr;
    
    if (curr != nullptr)
    {
        while (curr->person_p->getID() != idnum){
            curr = curr->next;
        }
        if (curr != nullptr){
            res = curr->person_p;
        }
    }
    
    return *res;
}



void PersonList::printList(){
    Node* curr = _head;
    
    while(curr != nullptr){
        cout << curr->person_p->getName() <<endl;
        curr = curr->next;
    }
}
