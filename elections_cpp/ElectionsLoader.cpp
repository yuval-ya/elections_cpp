#include <typeinfo>
#include "ElectionsLoader.h"
#include "SimpleElections.h"

namespace elections {

	Elections* ElectionsLoader::load(std::istream& in) {
		ElectionsType type;
		in.read(rcastc(&type), sizeof(type));
		if (!in.good()) {
			std::cout << "Error reading" << std::endl;
			exit(-1);
		}
		switch (type)
		{
		case ElectionsType::RERGULAR:
			return new Elections(in);
			break;
		case ElectionsType::SIMPLE:
			return new SimpleElections(in);
			break;
		default:
			return nullptr;
			break;
		}
	}

	bool ElectionsLoader::save(std::ostream& out, Elections* elections) {
		ElectionsType type;
		if (typeid(*elections) == typeid(Elections))
			type = ElectionsType::RERGULAR;
		else if (typeid(*elections) == typeid(SimpleElections))
			type = ElectionsType::SIMPLE;
		else
			return false;

		out.write(rcastcc(&type), sizeof(type));
		if (!out.good()) {
			std::cout << "Error writing" << std::endl;
			exit(-1);
		}
		return elections->save(out);
	}

}