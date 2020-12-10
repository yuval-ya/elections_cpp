//
//  PersonPtr.h
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 25/11/2020.
//  Copyright © 2020 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#pragma once
#include "Person.h"

class PersonPtr
{
    
    // Smart pointer to Person
    
    private:
        Person* _p;
        int*    _r;
        void release();
    public:
        PersonPtr();
        PersonPtr(const String&, int idnum, int year, District& district);
        PersonPtr(const PersonPtr&);
        PersonPtr(Person*);
        ~PersonPtr();

        PersonPtr& operator=(PersonPtr&);
        bool operator==(Person* pnt);
		bool operator!=(Person* pnt);
        Person* operator->() { return _p; }
        Person& operator*() { return *_p; }
};
