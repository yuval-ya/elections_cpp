#include <iostream>
using namespace std;

#include "String.h"

int main(void) {
	
	char name[100];

	cout << "hello" << endl;
	//cin >> name;
	String myname = "yuval";

	cout << myname;

	myname.set("tamir");
	cout << myname;
	return 0;

}