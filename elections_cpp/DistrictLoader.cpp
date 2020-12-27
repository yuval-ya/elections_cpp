#include "DistrictLoader.h"
#include <typeinfo>

namespace elections {

	District* DistrictLoader::load(std::istream& in) {
		DistrictType type;
		in.read(rcastc(&type), sizeof(type));
		if (!in.good()) {
			std::cout << "Error reading" << std::endl;
			exit(-1);
		}
		switch (type)
		{
		case DistrictType::DIVIDED:
			return new DividedDistrict(in);
			break;
		case DistrictType::UNIFIED:
			return new UnifiedDistrict(in);
			break;
		default:
			return nullptr;
			break;
		}
	}

	bool DistrictLoader::save(std::ostream& out, District* district) {
		DistrictType type;
		if (typeid(*district) == typeid(DividedDistrict))
			type = DistrictType::DIVIDED;
		else if (typeid(*district) == typeid(UnifiedDistrict))
			type = DistrictType::UNIFIED;
		else
			return false;
		
		out.write(rcastcc(&type), sizeof(type));
		if (!out.good()) {
			std::cout << "Error writing" << std::endl;
			exit(-1);
		}
		return district->save(out);

	}

}