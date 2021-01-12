#include <typeinfo>
#include "ElectionsLoader.h"

namespace elections {

Elections* ElectionsLoader::load(std::istream& in) {
    ElectionsType type;
    in.read(rcastc(&type), sizeof(type));
	if (!in.good()) throw File_Error("Unable to read from file");

    switch (type)
    {
        case ElectionsType::RERGULAR:
            return new Elections(in);
            break;
        case ElectionsType::SIMPLE:
            return new SimpleElections(in);
            break;
        default:
            throw File_Error("Invalid election type in the input file");
    }
}

void ElectionsLoader::save(std::ostream& out, Elections* elections) {
    ElectionsType type = ElectionsType::RERGULAR;
    
    if (typeid(*elections) == typeid(SimpleElections))
        type = ElectionsType::SIMPLE;
    
    out.write(rcastcc(&type), sizeof(type));
	if (!out.good()) throw File_Error("Unable to write to file");

    elections->save(out);
}

}
