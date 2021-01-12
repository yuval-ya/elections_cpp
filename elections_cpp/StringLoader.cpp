#include "StringLoader.h"
using namespace std;

string StringLoader::load(istream& in){
    int size = 0;
    char* tmpName = nullptr;
   
    try {
        in.read(rcastc(&size), sizeof(size));	
        tmpName = new char[size + 1];
        in.read(tmpName, size);
		if (!in.good()) throw File_Error("Unable to read from file");
        tmpName[size] = '\0';
        string name = tmpName;
        delete[] tmpName;
        
        return name;
    }
    catch (...) {
        if (tmpName)
            delete[] tmpName;
        throw;
    }
}

void StringLoader::save(ostream& out, const string& str) {
    int size = str.length();
    out.write(rcastcc(&size), sizeof(size));
    out.write(str.c_str(), size);

	if (!out.good()) throw File_Error("Unable to write to file");
}
