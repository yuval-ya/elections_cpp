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
    private:
        Person* _p;
        int*    _r;

        // releases inner Point - decreasing reference count
        // if ref==0, frees memory for point and count
        void release();
    public:
        PersonPtr();
        // allocates a new Point
        PersonPtr(const String&, int idnum, int year, int district_num);
        // joins ownership of other's Point
        PersonPtr(const PersonPtr&);

        // takes ownership of given Point
        PersonPtr(Person*);
        
        // done - can release reference to Point
        ~PersonPtr();

        // release current Point, join ownership of other's Point
        PersonPtr& operator=(PersonPtr&);

        // allow pointer-like access
        Person* operator->() { return _p; }
        Person& operator*() { return *_p; }
};
