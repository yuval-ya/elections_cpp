#include <typeinfo>
#include "ElectionsLoader.h"

namespace elections {

Elections* ElectionsLoader::load(std::istream& in) {
    ElectionsType type;
    in.read(rcastc(&type), sizeof(type));
    switch (type)
    {
        case ElectionsType::RERGULAR:
            return new Elections(in);
            break;
        case ElectionsType::SIMPLE:
            return new SimpleElections(in);
            break;
        default:
            throw std::runtime_error("Invalid election type in the input file");
    }
}

void ElectionsLoader::save(std::ostream& out, Elections* elections) {
    ElectionsType type = ElectionsType::RERGULAR;
    
    if (typeid(*elections) == typeid(SimpleElections))
        type = ElectionsType::SIMPLE;
    
    out.write(rcastcc(&type), sizeof(type));
    elections->save(out);
}

}
