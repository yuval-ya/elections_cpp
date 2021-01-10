#include "StringLoader.h"
using namespace std;

string StringLoader::load(istream& in){
    int size = 0;
    char* tmpName = nullptr;
    
    try {
        in.read(rcastc(&size), sizeof(size));
        tmpName = new char[size + 1];
        in.read(tmpName, size);
        tmpName[size] = '\0';
        string name = tmpName;
        delete[] tmpName;
        
        return name;
    }
    catch (const ifstream::failure& ex) {
        if (tmpName)
            delete[] tmpName;
        throw ex;
    }
}

void StringLoader::save(ostream& out, const string& str) {
    int size = str.length();
    out.write(rcastcc(&size), sizeof(size));
    out.write(str.c_str(), size);
}
