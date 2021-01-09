#include "StringLoader.h"

using namespace std;

string StringLoader::load(istream& in){
	
	int size = 0;
	in.read(rcastc(&size), sizeof(size));

	char* tmpName = new char[size + 1];
	in.read(tmpName, size);
	tmpName[size] = '\0';

	string name = tmpName;
	delete tmpName;

	if (!in.good()) {
		throw;
		/*
		*
		*
		*/
		exit(-1);
	}
	return name;
}

void StringLoader::save(ostream& out, const string& str) {
	
	int size = str.size();
	out.write(rcastcc(&size), sizeof(size));
	out.write(str.c_str(), size);

	if (!out.good()) {
		throw;
		/*
		*
		*
		*/
		exit(-1);
	}

}