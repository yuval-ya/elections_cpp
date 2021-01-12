#include "DistrictLoader.h"
#include <typeinfo>

namespace elections {

District* DistrictLoader::load(std::istream& in) {   
    DistrictType type;
    in.read(rcastc(&type), sizeof(type));
	if (!in.good()) throw File_Error("Unable to read from file");

    switch (type)
    {
        case DistrictType::DIVIDED:
            return new DividedDistrict(in);
            break;
        case DistrictType::UNIFIED:
            return new UnifiedDistrict(in);
            break;
        default:
            throw File_Error("Invalid district type in the input file");
            break;
    }
}

void DistrictLoader::save(std::ostream& out, District* district) {
    
    DistrictType type = DistrictType::DIVIDED;
    if (typeid(*district) == typeid(UnifiedDistrict))
        type = DistrictType::UNIFIED;

    out.write(rcastcc(&type), sizeof(type));
	if (!out.good()) throw File_Error("Unable to write to file");

    district->save(out);
}

}
