#include <iostream>
#include "PersonList.h"

using namespace std;

int main(void) {
    
    PersonList list;

    Person yuval = Person("Yuval", 1, 1, 1);
    Person tamir = Person("Tamir", 2, 2, 2);

    list.addPerson(yuval);
    list.addPerson(tamir);
    
    
    PersonList list2;
    
    list2.addPerson(list.getPerson(2));

    Person a = list2.getPerson(2);
    
    return 0;
}

