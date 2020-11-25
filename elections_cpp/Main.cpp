#include <iostream>
#include "PersonList.h"

using namespace std;

int main(void) {
    
      PersonList list;
        
        Person yuval = Person("Yuval", 1, 1, 1);
        Person tamir = Person("Tamir", 2, 2, 2);
        Person edi = Person("Edi", 3, 3, 3);

        list.addPerson(yuval);
        list.addPerson(tamir);
        list.addPerson(edi);
        
        PersonList list2;
        
        Person* yuval_ptr = &list.getPerson(1);
        list2.addPerson(yuval_ptr);

    return 0;
}

